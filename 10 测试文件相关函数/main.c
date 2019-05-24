#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"

#define isspace(c) (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')

typedef enum _dev_type {
	UART0 = 0,
	UART1 = 1,
	UART2 = 2,
	UART3 = 3,
	SPI0 = 4,
	SPI1 = 5,
	LED = 6,
	TX_E = 7,
	RX_E = 8,
	GLNA = 9,
	ZC = 10,

	DEV_TYPE_MAX = 0xff,
}dev_type;

typedef enum _dev_io {
	TX = 0,
	RX = 1,
	CS = 2,
	CLK = 3,
	MOSI = 4,
	MISO = 5,
	PWR = 6,
	RS485 = 7,
	PHASE_A = 8,
	PHASE_B = 9,
	PHASE_C = 10,

	DEV_IO_MAX = 0xff,
}dev_io;

typedef enum _uart_type {
	METER = 0,
	LOG = 1,
	CLI = 2,
	R485 = 3,
	IR = 4,

	UART_MAX = 0xff,
}uart_type;

static int is_whitespace(const char* text)
{
	while (*text != 0) {
		if (!isspace(*text))
			return 0;
		text++;
	}
	return 1;
}

static void chomp_trailing_whitespace(char* buf)
{
	unsigned len = strlen(buf);
	while (len > 0) {
		if (!isspace(buf[len - 1]))
			break;
		len--;
	}
	buf[len] = 0;
}

static int starts_with(const char* str, const char* prefix)
{
	return memcmp(str, prefix, strlen(prefix)) == 0;
}

int main()
{
	FILE* fp = NULL;
	fp = fopen("oem.ini", "r");
	char buf[2048];
	dev_type dev = DEV_TYPE_MAX;
	dev_io io = DEV_IO_MAX;
	uart_type uart = UART_MAX;
	if (fp == NULL)
		printf("file open failed!");
	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		if (buf[0] == '#')
			continue;
		if (is_whitespace(buf))
			continue;
		chomp_trailing_whitespace(buf);
		if (isspace(buf[0]))
		{
			printf("进入第一逻辑！，此时buf是：\n");
			printf("%s \n", buf);
			char* start = buf + 1;
			while (*start && isspace(*start))
				start++;
			io = DEV_IO_MAX;
			uart = UART_MAX;
			if (starts_with(start, "tx ")) {
				//printf("tx gpio:%d\n", atoi (peek_next_token (start)));
				io = TX;
			}
			else if (starts_with(start, "rx ")) {
				//printf("rx gpio:%d\n", atoi (peek_next_token (start)));
				io = RX;
			}
			else if (starts_with(start, "power ")) {
				//printf("power gpio:%d\n", atoi (peek_next_token (start)));
				io = PWR;
			}
			else if (starts_with(start, "rs485 ")) {
				//printf("rs485 gpio:%d\n", atoi (peek_next_token (start)));
				io = RS485;
			}
			else
				printf("未识别字段!\n");

			printf("开始调用配置函数！\n");
		}
		else
		{
			printf("进入第二逻辑，此时buf是：\n");
			printf("%s \n", buf);
			char* start = buf;
			//printf("\n%s\n", buf);

			while (*start && isspace(*start))
				start++;
			dev = DEV_TYPE_MAX;
			if (starts_with(start, "uart0")) {
				dev = UART0;
			}
			else if (starts_with(start, "uart1")) {
				dev = UART1;
			}
			else if (starts_with(start, "uart2")) {
				dev = UART2;
			}
			else if (starts_with(start, "uart3")) {
				dev = UART3;
			}
		}
	}
	fclose(fp);
	getchar();
}