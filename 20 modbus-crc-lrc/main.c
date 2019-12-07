#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

//unsigned char* auchMsg; /*按信息的字节计算LRC*/
//unsigned short usDataLen; /*按信息的字节计算LRC*/
static unsigned char LRC(unsigned char* auchMsg, unsigned short usDataLen)
{
	unsigned char uchLRC = 0; /*初始化LRC字符 */
	while (usDataLen--) /*通过数据缓冲器*/
		uchLRC += *auchMsg++; /*加缓冲器字节无进位*/
	return ((unsigned char)(-((char)uchLRC))); /*返回二进制补码*/
}

static uint8_t iot_modbus_task_check_lrc(uint8_t* data, uint16_t len)
{
	uint8_t temp_lrc = 0;
	while (len--)
		temp_lrc += *data++;
	//return ((uint8_t)(0-((char)temp_lrc)));
	return (~temp_lrc) + 1;
}

uint8_t lrc_check(uint8_t* data, uint8_t len)
{
	uint8_t i = 0;
	uint8_t sum = 0;
	uint8_t* lrc_data = NULL;
	lrc_data = malloc(len);
	/* preamble and check bit(2 bytes) and tail(2 byte)
	 * do not participate in LRC calculations
	 */
	uint8_t* temp_ptr = data + 1;
	for (i = 0; i < len - 1; i++)
	{
		if (data[i] >= 0x41)
			lrc_data[i] = temp_ptr[i] - 0x41 + 10;
		else
			lrc_data[i] = temp_ptr[i] - 0x30;
	}
	for (i = 0; i < (len - 1) / 2; i++)
	{
		sum += ((lrc_data[2 * i] << 4) + lrc_data[2 * i + 1]);
	}
	//os_mem_free(lrc_data);
	free(lrc_data);
	return (~sum) + 1;
}

void InvertUint8(unsigned char* dBuf, unsigned char* srcBuf)
{
	int i;
	unsigned char tmp[4];
	tmp[0] = 0;
	for (i = 0; i < 8; i++)
	{
		if (srcBuf[0] & (1 << i))
			tmp[0] |= 1 << (7 - i);
	}
	dBuf[0] = tmp[0];
}

void InvertUint16(unsigned short* dBuf, unsigned short* srcBuf)
{
	int i;
	unsigned short tmp[4];
	tmp[0] = 0;
	for (i = 0; i < 16; i++)
	{
		if (srcBuf[0] & (1 << i))
			tmp[0] |= 1 << (15 - i);
	}
	dBuf[0] = tmp[0];
}

unsigned short CRC16_MODBUS(unsigned char* puchMsg, unsigned int usDataLen)
{
	unsigned short wCRCin = 0xFFFF;
	unsigned short wCPoly = 0x8005;
	unsigned char wChar = 0;

	while (usDataLen--)
	{
		wChar = *(puchMsg++);
		InvertUint8(&wChar, &wChar);
		wCRCin ^= (wChar << 8);
		for (int i = 0; i < 8; i++)
		{
			if (wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	InvertUint16(&wCRCin, &wCRCin);
	return (wCRCin);
}

//3A 31 45 30 33 30 30 30 30 30 30 36 34 37 42 0D 0A    :1E03000000647B..
//uint8_t test[] = "1E0300000064";
//uint8_t test[] = { 0x1E, 0x03, 0x00,0x00,0x00,0x64 };
uint8_t test_2[] = { 0x3A, 0x31, 0x45, 0x30, 0x33, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x36, 0x34, 0xaa, 0xbb, 0x0d, 0x0c };

uint8_t test_3[] = "......";
uint8_t test_4[] = { 0x1E, 0x03, 0x00, 0x00, 0x00, 0x0A };

//uint8_t test_5[] = { 0x3A, 0x30, 0x33, 0x31, 0x31 };//EC
uint8_t test_5[] = { 0x3A, 0x30, 0x33, 0x31, 0x31, 0x00, 0x00, 0x0D, 0x0A };//EC
uint8_t test_6[] = ":031100..";
uint8_t test_7[] = { 0x3A,0x30,0x33,0x30,0x33,0x30,0x30,0x30 ,0x30 ,0x30,0x30,0x30,0x41, 0x00, 0x00, 0x0D, 0x0A };//AF

int main()
{
	uint8_t* test = test_5;
	uint8_t len = sizeof(test_5);
	printf("test:%p, test_7:%p \n", test, test_5);
	printf("data:");
	for (uint8_t i = 0; i < len; i++)
	{
		printf("%X ", test[i]);
	}
	printf("\n");
	uint8_t temp_lrc_8 = LRC(test, len);
	printf("%X \n", temp_lrc_8);
	uint8_t temp_lrc = iot_modbus_task_check_lrc(test, len);
	printf("%X \n", temp_lrc);
	uint8_t temp_lrc_7 = lrc_check(test, len);
	printf("%X \n", temp_lrc_7);
	uint8_t temp_lrc_2 = iot_modbus_task_check_lrc(test, len);
	printf("%X \n", temp_lrc_2);

	uint16_t temp_lrc_3 = CRC16_MODBUS(test, len);
	printf("%X \n", temp_lrc_3);
	uint16_t temp_lrc_4 = CRC16_MODBUS(test, len);
	printf("%X \n", temp_lrc_4);

	uint16_t temp_lrc_5 = CRC16_MODBUS(test, len);
	printf("%X \n", temp_lrc_5);
	uint16_t temp_lrc_6 = CRC16_MODBUS(test, len);
	printf("%X \n", temp_lrc_6);
	getchar();
	return 0;
}