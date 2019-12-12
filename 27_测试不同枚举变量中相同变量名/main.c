//结论：
//1.如果枚举定义在宏定义之前，则枚举变量与宏定义 不能定义为相同名字
//2.如果枚举定义在宏定义之后，则枚举中的变量将被替换
//---------宏定义将替换在其定义之后出现的字符------------

#include "stdio.h"

//#include "define.h"
#include "typedef.h"



//typedef enum _io_type {
//	led_tx = 1,
//	led_rx = 2,
//	gpio_1 = 3,
//	gpio_2 = 4,
//	gpio_3,
//	gpio_4,
//};

//#define led_rx 5

typedef enum _io_type io_type;
typedef enum _io_type led_type;

//typedef enum _led_type {
//	led_tx = 3,
//	led_rx = 4,
//}led_type;

int main()
{
	io_type io_2;
	io_2 = gpio_2;

	io_type io_3 = led_rx;

	led_type led;
	led = led_rx;
	printf("io_2:%d, io_3: %d, led:%d\n", io_2,io_3,led);
	getchar();
	return 0;
}