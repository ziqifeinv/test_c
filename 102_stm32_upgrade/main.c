#include "port.h"
#include "serial.h"
#include "binary.h"
#include "parser.h"
#include "stm32.h"

//common
#include "stdio.h"
#include "stdint.h"
#include "windows.h"

#define FILE_TYPE 0 //1->*.bin   0->*.txt

parser_t *parser = &PARSER_BINARY;

void *p_st = NULL;
FILE *diag;
struct port_interface *port = NULL;
char init_flag  = 1;
uint32_t addr_start = 0x0;
uint32_t addr_end = 0x0;
uint8_t verify = 1;
uint8_t download_retry_number = 10;

char *filename = "D:\\workspace\\vsc\\single-file\\test_c\\102_stm32_upgrade\\f103ret6.bin";

/* settings */
struct port_options port_opts = {
	.device			= "COM6",
	.baudRate		= SERIAL_BAUD_115200,
	.serial_mode		= "8e1",
	.bus_addr		= 0,
	.rx_frame_max		= STM32_MAX_RX_FRAME,
	.tx_frame_max		= STM32_MAX_TX_FRAME,
};

int main()
{
    int ret = 0;
    parser_err_t perr;
    stm32_err_t s_err;
    diag = stdout;

    //init parser
    p_st = parser->init();
    if (p_st == NULL) {
        fprintf(stderr, "%s Parser failed to initialize\n", parser->name);
        goto close;
    }
    perr = parser->open(p_st, filename, 0);
    if (perr != PARSER_ERR_OK) {
        fprintf(stderr, "%s ERROR: %s\n", parser->name, parser_errstr(perr));
        if (perr == PARSER_ERR_SYSTEM) perror(filename);
        goto close;
    }
    fprintf(diag, "Succeed to open file, Using Parser : %s\n", parser->name);

    //init port
    if (port_open(&port_opts, &port) != PORT_ERR_OK) {
		fprintf(stderr, "Failed to open port: %s\n", port_opts.device);
		goto close;
	}
    fprintf(diag, "Succeed to open port, Interface %s: %s\n", port->name, port->get_cfg_str(port));

    //connect stm32
    stm = stm32_init(port, init_flag);
	if (!stm) {
        goto close;
    }
    fprintf(diag, "Version      : 0x%02x\n", stm->bl_version);
	if (port->flags & PORT_GVR_ETX) {
		fprintf(diag, "Option 1     : 0x%02x\n", stm->option1);
		fprintf(diag, "Option 2     : 0x%02x\n", stm->option2);
	}
	fprintf(diag, "Device ID    : 0x%04x (%s)\n", stm->pid, stm->dev->name);
	fprintf(diag, "- RAM        : Up to %dKiB  (%db reserved by bootloader)\n", (stm->dev->ram_end - 0x20000000) / 1024, stm->dev->ram_start - 0x20000000);
	fprintf(diag, "- Flash      : Up to %dKiB (size first sector: %dx%d)\n", (stm->dev->fl_end - stm->dev->fl_start ) / 1024, stm->dev->fl_pps, stm->dev->fl_ps[0]);
	fprintf(diag, "- Option RAM : %db\n", stm->dev->opt_end - stm->dev->opt_start + 1);
	fprintf(diag, "- System RAM : %dKiB\n", (stm->dev->mem_end - stm->dev->mem_start) / 1024);

    //upgrade
    uint32_t file_size = 0;
    uint8_t page_start = 0, page_end = 0, page_num = 0;
    uint32_t offset = 0, len = 0;
    uint32_t max_wlen = 0, max_rlen = 0;
    uint32_t addr_temp = 0;
    uint8_t buffer[256];
    uint8_t retry_counter = 0;

#if (FILE_TYPE == 1)
    file_size = parser->size(p_st);
#else
    static const uint8_t stm32_bin[] = {
        #include "test.txt"
    };
    file_size = sizeof(stm32_bin) / sizeof(uint8_t);
#endif
    if (file_size <= 0) {
        goto close;
    }
    addr_start = 0x0 + stm->dev->fl_start;
    addr_end = addr_start + file_size;
    page_start = flash_addr_to_page_floor(addr_start);
    page_num = flash_addr_to_page_ceil(addr_end) - page_start;
    s_err = stm32_erase_memory(stm, page_start, page_num);
    if (s_err != STM32_ERR_OK) {
        fprintf(stderr, "Failed to erase memory, start page:%d, page number:%d\n", page_start, page_num);
        goto close;
    }
    addr_temp = addr_start;
    max_wlen = port_opts.tx_frame_max - 2;	/* skip len and crc */
    max_wlen &= ~3;	/* 32 bit aligned */

    max_rlen = port_opts.rx_frame_max;
    max_rlen = max_rlen < max_wlen ? max_rlen : max_wlen;
    while(addr_temp < addr_end && offset < file_size) {
        uint32_t left	= addr_end - addr_temp;
        len		= max_wlen > left ? left : max_wlen;
        len		= len > file_size - offset ? file_size - offset : len;
#if (FILE_TYPE == 1)
        if (parser->read(p_st, buffer, &len) != PARSER_ERR_OK)
            goto close;
        if (len == 0) {
            fprintf(stderr, "Failed to read input file\n");
            goto close;
        }
#else
        memcpy(buffer, &stm32_bin[offset], len);
#endif
        again:
        s_err = stm32_write_memory(stm, addr_temp, buffer, len);
        if (s_err != STM32_ERR_OK) {
            fprintf(stderr, "Failed to write memory at address 0x%08x\n", addr_temp);
            goto close;
        }

        if (verify) {
            uint8_t compare[len];
            unsigned int offset, rlen;

            offset = 0;
            while (offset < len) {
                rlen = len - offset;
                rlen = rlen < max_rlen ? rlen : max_rlen;
                s_err = stm32_read_memory(stm, addr_temp + offset, compare + offset, rlen);
                if (s_err != STM32_ERR_OK) {
                    fprintf(stderr, "Failed to read memory at address 0x%08x\n", addr_temp + offset);
                    goto close;
                }
                offset += rlen;
            }

            for(uint32_t r = 0; r < len; ++r)
                if (buffer[r] != compare[r]) {
                    if (retry_counter == download_retry_number) {
                        fprintf(stderr, "Failed to verify at address 0x%08x, expected 0x%02x and found 0x%02x\n",
                            (uint32_t)(addr_temp + r),
                            buffer [r],
                            compare[r]
                        );
                        goto close;
                    }
                    ++retry_counter;
                    goto again;
                }

            retry_counter = 0;
        }

        addr_temp	+= len;
        offset	+= len;

        fprintf(diag,
            "\rWrote %saddress 0x%08x (%.2f%%) ",
            verify ? "and verified " : "",
            addr_temp,
            (100.0f / file_size) * offset
        );
        fflush(diag);

    }

    fprintf(diag,	"Done.\n");
    ret = 0;
    // goto close;

    //start app
    fprintf(diag, "\nStarting execution at address 0x%08x... ", addr_start);
    fflush(diag);
    if (stm32_go(stm, addr_start) == STM32_ERR_OK) {
        fprintf(diag, "done.\n");
    } else {
        fprintf(diag, "failed.\n");
    }


    // while (1) {
    //     uint8_t cmd_temp = 0x7f;
    //     perr = port->write(port, &cmd_temp, 1);
    //     if (perr != PORT_ERR_OK) {
    //         fprintf(diag, "port send failed\n");
    //         goto close;
    //     }
    //     Sleep(500);
    // }

close:
    if (p_st) {
        parser->close(p_st);
    }
    if (port) {
        port->close(port);
    }

    return ret ? 1 : 0;
}