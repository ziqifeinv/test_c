//���ۣ�
//1.���ö�ٶ����ں궨��֮ǰ����ö�ٱ�����궨�� ���ܶ���Ϊ��ͬ����
//2.���ö�ٶ����ں궨��֮����ö���еı��������滻
//---------�궨�彫�滻���䶨��֮����ֵ��ַ�------------

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