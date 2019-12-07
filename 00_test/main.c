
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

void func_1()
{
	char test = 0;
	test = test ^ 3 ^ 4 ^ 5;
	printf("test is %d", test);
#if 0
	printf("十进制： %d\n", 256);
	printf("16进制： %x\n", 256);
#endif
	getchar();
	return 0;
}

void func_2_1()
{
	printf("******** func_2 *************\n");
	
		static num = 5;
		num++;
		printf("%d \n", num);
		if (num > 8) {
			
			num = 0;
			printf("******** 88888 *************\n");
		}
	
}

void func_2()
{
	for (int i = 0; i < 20; i++)
	{
		printf("%d", i);
		func_2_1();
	}
}

typedef uint32_t iot_isr_t(uint32_t vector, uint32_t data);
typedef struct iot_interrupt
{
	uint8_t         vector;
	uint8_t         priority;
	uint8_t         cpu;
	uint8_t         rsvd;
	iot_isr_t* isr;
	uint32_t  data;
} iot_interrupt;

void func_3(uint32_t interrupt)
{
	iot_interrupt* intr = (iot_interrupt * )interrupt;
	
	printf("interrupt is : %x \n", interrupt);
	printf("interrupt addr is : %p \n", &interrupt);
	printf("intr addr is : %p \n", intr);
	uint32_t vector = intr->vector;
	uint32_t cpu = intr->cpu;
	printf("vector is : %d \n", vector);
	printf("cpu is : %d \n", cpu);
}

void func_4()
{
	printf("十进制:%d \n", 0b11);
	printf("十六进制:%x \n", 0b11);
}

int* func_5_1()
{
	int test = 12345;
	return &test;
}

void func_5()
{
	int* data = NULL;
	data = func_5_1();
	printf("data is :%d", *data);
}

typedef struct _adc_data {
	uint32_t channel_1_data;
	uint32_t channel_2_data;
	uint32_t channel_x_data[4];
}adc_data;

typedef struct _adc_t
{
	uint8_t channel;
	uint8_t used;
	adc_data data;
}adc_t;

void func_6()
{
	adc_t adc;
	adc_t *adc_p = &adc;
	uint8_t* channel = NULL;
	uint32_t* data =  NULL;
	uint32_t* data_1 = NULL;
	adc_p->channel = 1;
	printf("channel 1:%d\n", adc_p->channel);
	channel = &adc_p->channel;
	*channel = 2;
	printf("channel 2:%d\n", adc_p->channel);
	printf("channel 3:%d\n", *channel);
	printf("channel 4:%d\n", channel);
	adc_p->data.channel_1_data = 22;
	data = &adc_p->data.channel_1_data;
	adc_p->data.channel_x_data[0] = 33;
	adc_p->data.channel_x_data[1] = 44;
	data_1 = adc_p->data.channel_x_data;
	printf("data1:%d\n", adc_p->data.channel_1_data);
	printf("data2:%d\n", *data);
	printf("data3:%d\n", *data_1);
	printf("data3:%d\n", *(data_1+0x32));
}

long func_7_1()
{
	int a = -123;
	printf("a:%d \n", a);
	return a;
}
void func_7()
{
	long buf_offset = 0;
	buf_offset = func_7_1();
	printf("buf_offset:%d \n", buf_offset);
}

#define iot_grapp_aes_get_padding_len(x)    (((x) + 0xF) & (~0xF))
#define iot_grapp_aes_get_key(key, dest_mac, seq)   do{ \
    memcpy(key, dest_mac, 6); \
    key[6] = (seq >> 8) & 0xFF; \
    key[7] = seq & 0xFF; \
    } while(0)
void func_8()
{
	int data_len = 3;
	int len_1 = data_len / 16;
	int len_2 = data_len % 16;
	int len_3 = ((data_len % 16) ? 1 : 0);
	int buffer_len = (((data_len / 16) + ((data_len % 16) ? 1 : 0)) * 16);
	int buffer_len_2 = iot_grapp_aes_get_padding_len(data_len);
	uint8_t delta_len = buffer_len - data_len;
	printf("len1:%d, len2:%d, len3:%d, buffer_len:%d, buffer_len_2:%d, delta_len:%d \n", len_1, len_2, len_3, buffer_len, buffer_len_2,delta_len);

	uint8_t key[16] = { 0 };
	uint8_t dest_mac[6] = { 0xff,0xff,0xff,0xff,0xff,0xff };
	iot_grapp_aes_get_key(key, dest_mac, 0x1234);
	for (uint8_t i = 0; i < 16; i++) {
		printf("%x ", key[i]);
	}
}

typedef struct _data_t {
	uint8_t preamble;
	//uint8_t	data[0];
	uint8_t* data;
}data_t;

void func_9()
{
	uint8_t data[16] = { 0 };
	uint8_t data_1[15] = { 1,2,3,4,5,6,7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf };
	data_t *data_2 = malloc(sizeof(data_t));
	data_2->data = data_1;

	memset(data, 0, sizeof(data));
	data[0] = 0xaa;
	memcpy(&data[1], data_2->data, 15);
	for (uint8_t i = 0; i < 16; i++)
	{
		printf("%x ", data[i]);
	}
	printf("\n");
	
	//memmove(data_2->data, data_1, sizeof(data_1));
	memcpy(data_2->data, data_1, 15);
	for (uint8_t i = 0; i < 16; i++)
	{
		printf("%x ", data_2->data[i]);
	}
	printf("\n");
}

void func_10_1()
{
	static uint8_t a = 3;
	uint8_t b = 4;
	printf("a value:%d,%p \n", a, &a);
	printf("b value:%d,%p \n", b, &b);
}
void func_10()
{
	for (uint8_t i = 0; i < 3; i++)
	{
		printf("call number:%d \n", i);
		func_10_1();
		printf("\n");
	}
}

void func_11()
{
	for (uint8_t i = 0; i < 10; i++)
	{
		printf("%d ", i);
	}
}

void func_12()
{
	uint32_t addr_int = 0x11111111;
	uint32_t* addr_p = NULL;
	addr_p = (uint32_t*)addr_int;
	printf("addr_int:%x, addr_p:%p \n", addr_int, addr_p);
}

void func_13()
{
	uint8_t i = 0;
	for (i = 0; i < 100; i++)
	{
		printf("i:%d,%c \n", i, (char)i);
	}
}

void func_14()
{
	uint32_t a = 0;
	int b = (a - 1);
	printf("a:%lu, b;%d \n", a, b);
}

#define efuse_addr_check(offset) do{if(offset < 100){offset += 200;}}while(0)
#define efuse_read(offset) offset += efuse_addr_check(offset)
void func_15()
{
#define GPIO_PIN_NUMBER 65
	uint32_t offset = 100;
	printf("0 offset:%d\n", offset);
	//efuse_addr_check(offset);
	efuse_addr_check(offset);
	printf("1 offset:%d\n", offset);
	printf("gpio group test :%d \n", ((GPIO_PIN_NUMBER & 0x1F) ? \
		((GPIO_PIN_NUMBER >> 5) + 1) : (GPIO_PIN_NUMBER >> 5)));
}

void func_16()
{
	uint8_t a = 11;
	const uint8_t* ptr = &a;
	printf("1 ptr_addr:%p, ptr:%p, value:%d \n", &ptr, ptr, *ptr);
	uint8_t b = 22;
	ptr = &b;
	printf("2 ptr_addr:%p, ptr:%p, value:%d \n", &ptr, ptr, *ptr);
}

int main()
{
	func_16();
	getchar();
	return 0;
}
