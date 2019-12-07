

#include <stdio.h>
#include <stdint.h>

#define IOT_ABS(x) ((x) > 0 ? (x) : -(x))

uint8_t t_u8 = 0xff;
int8_t t_int8 = -129;
uint16_t t_u16 = 0xffff;
int16_t t_int16 = -32768;
uint32_t t_u32 = 123;
int t_int = -123;
float t_float = 12.3;
float t_float_2 = -12.3;

int main()
{
	printf("u8:%d, ads u8:%d: \n", t_u8, IOT_ABS(t_u8));
	printf("int8:%d, ads int8:%d: \n", t_int8, IOT_ABS(t_int8));

	printf("t_u16:%d, ads t_u16:%d: \n", t_u16, IOT_ABS(t_u16));
	printf("t_int16:%d, ads t_int16:%d: \n", t_int16, IOT_ABS(t_int16));

	//printf("u32:%d, ads u32:%d: \n", t_u32, IOT_ABS(t_u32));
	printf("int:%d, ads int:%d: \n", t_int, IOT_ABS(t_int));

	printf("t_float:%d, ads t_float:%d: \n", (int)t_float, (int)IOT_ABS(t_float));
	printf("t_float_2:%d, ads t_float_2:%d \n", (int)t_float_2, (int)IOT_ABS(t_float_2));
	getchar();
	return 0;
}