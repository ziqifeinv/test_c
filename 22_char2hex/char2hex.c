
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//char valueToHexCh(const int value)
//{
//	char result = "\0";
//	if (value >= 0 && value <= 9) {
//		result = (char)(value + 48); //48为ascii编码的‘0’字符编码值
//	}
//	else if (value >= 10 && value <= 15) {
//		result = (char)(value - 10 + 65); //减去10则找出其在16进制的偏移量，65为ascii的‘A‘的字符编码值
//	}
//	else {
//		;
//	}
//
//	return result;
//}
//
//int strToHex(char* ch, char* hex)
//{
//	int high, low;
//	int tmp = 0;
//	if (ch == NULL || hex == NULL) {
//		return -1;
//	}
//
//	if (strlen(ch) == 0) {
//		return -2;
//	}
//
//	while (*ch) {
//		tmp = (int)*ch;
//		
//		*hex++ = valueToHexCh(tmp); //先写高字节
//		//*hex++ = valueToHexCh(low); //其次写低字节
//		ch++;
//	}
//	*hex = "\0";
//	return 0;
//}

char  AsciiToHex(unsigned char* pAscii, unsigned char* pHex, int nLen)
{
	int nHexLen = nLen / 2;
	unsigned char Nibble[2] = { 0 };
	int i = 0;
	int j = 0;

	if (nLen % 2)
	{
		return 1;
	}

	for (i = 0; i < nHexLen; i++)
	{
		Nibble[0] = *pAscii++;
		Nibble[1] = *pAscii++;
		for (j = 0; j < 2; j++)
		{
			if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
				Nibble[j] = Nibble[j] - 'A' + 10;
			else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
				Nibble[j] = Nibble[j] - 'a' + 10;
			else if (Nibble[j] >= '0' && Nibble[j] <= '9')
				Nibble[j] = Nibble[j] - '0';
			else
				return 1;//Nibble[j] = Nibble[j] - 'a' + 10;

		}	// for (int j = ...)
		pHex[i] = Nibble[0] << 4;	// Set the high nibble
		pHex[i] |= Nibble[1];	//Set the low nibble
	}	// for (int i = ...)
	return 0;
}

unsigned int str_hex(unsigned char* str, unsigned char* hex)
{
	unsigned char ctmp, ctmp1, half;
	unsigned int num = 0;
	do {
		do {
			half = 0;
			ctmp = *str;
			if (!ctmp) break;
			str++;
		} while ((ctmp == 0x20) || (ctmp == 0x2c) || (ctmp == '\t'));
		if (!ctmp) break;
		if (ctmp >= 'a') ctmp = ctmp - 'a' + 10;
		else if (ctmp >= 'A') ctmp = ctmp - 'A' + 10;
		else ctmp = ctmp - '0';
		ctmp = ctmp << 4;
		half = 1;
		ctmp1 = *str;
		if (!ctmp1) break;
		str++;
		if ((ctmp1 == 0x20) || (ctmp1 == 0x2c) || (ctmp1 == '\t'))
		{
			ctmp = ctmp >> 4;
			ctmp1 = 0;
		}
		else if (ctmp1 >= 'a') ctmp1 = ctmp1 - 'a' + 10;
		else if (ctmp1 >= 'A') ctmp1 = ctmp1 - 'A' + 10;
		else ctmp1 = ctmp1 - '0';
		ctmp += ctmp1;
		*hex = ctmp;
		hex++;
		num++;
	} while (1);
	if (half)
	{
		ctmp = ctmp >> 4;
		*hex = ctmp;
		num++;
	}
	return(num);


}

uint16_t CharToHex(unsigned char bHex)
{
	/*uint8_t num_h = (bHex >> 4) & 0xF;
	uint8_t num_l = bHex & 0xF;*/
	uint8_t temp_num[2] = { 0 };
	temp_num[0] = (bHex >> 4) & 0xF;
	temp_num[1] = bHex & 0xF;
	for (int8_t i = 0; i < 2; i++){
		if ((temp_num[i] >= 0) && (temp_num[i] <= 9))
		{
			temp_num[i] += 0x30;
		}
		else if ((temp_num[i] >= 10) && (temp_num[i] <= 15))//Capital
		{
			temp_num[i] += 0x37;
		}
		else
		{
			temp_num[i] = 0xff;
		}
	}
	printf("H:%x,L%x \n", temp_num[0] << 8, temp_num[1]);
	return ((temp_num[0] << 8) + temp_num[1]);
}

int main(void)
{
	unsigned char test[] = "";
	unsigned char hex[100] = { 0 };
	uint8_t test_1 = 0x00;
	uint16_t hex_1 = 0x0000;
	//int res = str_hex(test, hex);
	//printf("res:%d \n", res);
	
	printf("test:%s \n", test);
	printf("test:%x \n", '11');
	hex_1 = CharToHex(test_1);
	printf("hex_1:%x \n", hex_1);
	/*for (int i = 0; i < sizeof(test); i++)
	{
		hex[i] = CharToHex(test[i]);
		printf("%X ", hex[i]);
	}
	printf("\n");*/
	getchar();
	return 0;
}