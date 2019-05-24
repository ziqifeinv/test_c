//结论：枚举变量不能定义为相同名字

#include "stdio.h"

typedef enum _io_type {
	led_tx = 1,
	led_rx = 2,
}io_type;

typedef enum _led_type {
	led_tx = 3,
	led_rx = 4,
}led_type;

int main()
{
	io_type io;
	io = led_rx;
	printf("io:%d\n", io);
	getchar();
	return 0;
}