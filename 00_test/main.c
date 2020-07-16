
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
	printf("閸椾浇绻橀崚璁圭窗 %d\n", 256);
	printf("16鏉╂稑鍩楅敍? %x\n", 256);
#endif
	getchar();
	return;
}

void func_2_1()
{
	printf("******** func_2 *************\n");

	static int num = 5;
	num++;
	printf("%d \n", num);
	if (num > 8)
	{

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
	uint8_t vector;
	uint8_t priority;
	uint8_t cpu;
	uint8_t rsvd;
	iot_isr_t *isr;
	uint32_t data;
} iot_interrupt;

void func_3(uint32_t interrupt)
{
	iot_interrupt *intr = (iot_interrupt *)interrupt;

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
	printf("閸椾浇绻橀崚?:%d \n", 0b11);
	printf("閸椾礁鍙氭潻娑樺煑:%x \n", 0b11);
}

int *func_5_1()
{
	int test = 12345;
	return &test;
}

void func_5()
{
	int *data = NULL;
	data = func_5_1();
	printf("data is :%d", *data);
}

typedef struct _adc_data
{
	uint32_t channel_1_data;
	uint32_t channel_2_data;
	uint32_t channel_x_data[4];
} adc_data;

typedef struct _adc_t
{
	uint8_t channel;
	uint8_t used;
	adc_data data;
} adc_t;

void func_6()
{
	adc_t adc;
	adc_t *adc_p = &adc;
	uint8_t *channel = NULL;
	uint32_t *data = NULL;
	uint32_t *data_1 = NULL;
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
	printf("data3:%d\n", *(data_1 + 0x32));
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

#define iot_grapp_aes_get_padding_len(x) (((x) + 0xF) & (~0xF))
#define iot_grapp_aes_get_key(key, dest_mac, seq) \
	do                                            \
	{                                             \
		memcpy(key, dest_mac, 6);                 \
		key[6] = (seq >> 8) & 0xFF;               \
		key[7] = seq & 0xFF;                      \
	} while (0)
void func_8()
{
	int data_len = 3;
	int len_1 = data_len / 16;
	int len_2 = data_len % 16;
	int len_3 = ((data_len % 16) ? 1 : 0);
	int buffer_len = (((data_len / 16) + ((data_len % 16) ? 1 : 0)) * 16);
	int buffer_len_2 = iot_grapp_aes_get_padding_len(data_len);
	uint8_t delta_len = buffer_len - data_len;
	printf("len1:%d, len2:%d, len3:%d, buffer_len:%d, buffer_len_2:%d, delta_len:%d \n", len_1, len_2, len_3, buffer_len, buffer_len_2, delta_len);

	uint8_t key[16] = {0};
	uint8_t dest_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	iot_grapp_aes_get_key(key, dest_mac, 0x1234);
	for (uint8_t i = 0; i < 16; i++)
	{
		printf("%x ", key[i]);
	}
}

typedef struct _data_t
{
	uint8_t preamble;
	//uint8_t	data[0];
	uint8_t *data;
} data_t;

void func_9()
{
	uint8_t data[16] = {0};
	uint8_t data_1[15] = {1, 2, 3, 4, 5, 6, 7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
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
	uint32_t *addr_p = NULL;
	addr_p = (uint32_t *)addr_int;
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

#define efuse_addr_check(offset) \
	do                           \
	{                            \
		if (offset < 100)        \
		{                        \
			offset += 200;       \
		}                        \
	} while (0)
#define efuse_read(offset) offset += efuse_addr_check(offset)
void func_15()
{
#define GPIO_PIN_NUMBER 65
	uint32_t offset = 100;
	printf("0 offset:%d\n", offset);
	//efuse_addr_check(offset);
	efuse_addr_check(offset);
	printf("1 offset:%d\n", offset);
	printf("gpio group test :%d \n", ((GPIO_PIN_NUMBER & 0x1F) ? ((GPIO_PIN_NUMBER >> 5) + 1) : (GPIO_PIN_NUMBER >> 5)));
}

void func_16()
{
	uint8_t a = 11;
	const uint8_t *ptr = &a;
	printf("1 ptr_addr:%p, ptr:%p, value:%d \n", &ptr, ptr, *ptr);
	uint8_t b = 22;
	ptr = &b;
	printf("2 ptr_addr:%p, ptr:%p, value:%d \n", &ptr, ptr, *ptr);
}

void func_17()
{
	uint8_t a = 11;
	uint8_t b = 22;
	uint8_t *table[1] = {
		&a,
	};
	printf("a:%d, table a:%d \n", a, *table[0]);
	printf("1 is %s\n", (1 ? "true" : "false"));

	uint8_t c = 33;
	void *p_temp = NULL;
	p_temp = (void *)&c;
	printf("addr c:%p, addr p_temp:%p, p_temp:%p\n", &c, p_temp, &p_temp);
}

void func_18()
{
	typedef struct _test_t
	{
		uint8_t a : 1,
			b : 1,
			c : 2,
			d : 4;
	} test_t;

	char aa[7] = "hello";
	char bb[7] = "world";
	char *aa_1 = &aa;

	test_t cc = {0b0000001};
	test_t dd = {0b0000010};
	printf("cc.a:%d \n", cc.a);
	cc = dd;
	printf("cc.a:%d \n", cc.a);

	printf("aa:%s, bb:%s \n", aa, bb);
	*aa_1 = bb;
	printf("aa:%s, bb:%s \n", aa, bb);

	test_t xxx = {0};
	uint8_t *temp_p = &xxx;
	printf("xxx addr:%p \n", temp_p);

	printf("a:%d, b:%d, c:%d, d:%d \n", xxx.a, xxx.b, xxx.c, xxx.d);
	xxx.b = 1;
	printf("a:%d, b:%d, c:%d, d:%d \n", xxx.a, xxx.b, xxx.c, xxx.d);
}

void func_19()
{
#define RX_TIMEOUT_TRANSFORM(x) ((25 * (x) > 127) ? 127 \
												  : ((25 * (x) < 94) ? 94 : (25 * (x))))

	uint8_t x = 6;
	x = RX_TIMEOUT_TRANSFORM(x);
	printf("x:%d \n", x);
}

//濞村??鐦?楠炶櫕绮﹂崝鐔诲厴閿涘苯婀?婢х偤鍣烘潏鍐ㄧ毈閺冩湹濞囬悽鈺?loat閸滃?╪t閻ㄥ嫬灏?閸??
float func_20_1(uint8_t actual_pos, float last_pos)
{
	float actual_pos_f = (float)actual_pos;
	float last_pos_f = (float)last_pos;
	float temp = 0.0;
	float temp_dec = 0.0;
	float result = 0.0;
	temp = actual_pos_f * 0.2 + last_pos_f * 0.8;
	temp_dec = temp - (int)temp;
	// result = (uint8_t)temp + (temp_dec >= 0.5 ? 1: 0);
	result = temp;
	printf("last pos:%f -f:%f, actual pos:%d -f:%f, temp:%f -uint8:%d, temp_dev:%f, result:%f -uint8:%d \n",
		   last_pos, last_pos_f, actual_pos, actual_pos_f, temp, (uint8_t)temp, temp_dec, result, (uint8_t)result);
	return result;
}
void func_20() //float 閸欐牗鏆?
{
	// for(uint8_t i = 2; i < 20; i += 2) {
	// 	(void)func_20_1(i, i - 1);
	// }
	float result = 0;
	result = func_20_1(13, 12);
	result = func_20_1(13, result);
	result = func_20_1(13, result);
	result = func_20_1(13, result);
	result = func_20_1(13, result);
}

void func_21_1(uint8_t *buf, uint32_t len)
{
	printf("the array is: ");
	for (uint32_t i = 0; i < len; i++)
	{
		printf("%d ", buf[i]);
	}
	printf("\n");
}
void func_21()
{
	uint8_t arr[2][2] = {{1, 2}, {3, 4}};
	func_21_1(arr[0], 2);
}

#if 0
unsigned long *preuso_noise_sequence(        ){
    static unsigned long preamble_vec[7];
    unsigned long register_state[7] =
        {0x1a1, 0x13b, 0x1f2, 0x18b, 0x141, 0x11f, 0x1ff};
    for(uint8_t j = 0; j < 7; j++){
        unsigned long preuso_noise_seq = 0, temp = 0;
        for(uint8_t i = 0; i < 32; i++){
            temp = (register_state[j] >> 3 & 1)
                ^ (register_state[j] >> (9 - 1) & 1);
            //printf("temp is :%d\n",temp);
            register_state[j] = (register_state[j] << 1 & 0x1ff) ^ temp;
            //printf("state is %4x\n",register_state);
            preuso_noise_seq += temp << i;
            //printf("seq is %4x\n",preuso_noise_seq);
        }
        //printf("seq is %4x\n",preuso_noise_seq);
        preamble_vec[j] = preuso_noise_seq;
    }
    return preamble_vec;
}
#else
const unsigned long preamble_list[7] = {0x7AEA2433, 0x4E5586F4, 0xE9B9142B,
										0x1732094E, 0xFBA0D6DD, 0x7787FC1E, 0xF6CD0EF0};

const unsigned long *preuso_noise_sequence()
{
	return &preamble_list[0];
}
#endif
void func_22()
{
	unsigned long *result = NULL;
	result = preuso_noise_sequence();
	printf("result :");
	for (uint8_t i = 0; i < 7; i++)
	{
		printf("0x%08X, ", result[i]);
	}
	printf("\n");
	return;
}

//获取时间和日历并创建以日历为名称的log文件
#include <time.h>
void func_23()
{
	time_t raw_time = 0;
	struct tm *info = NULL;
	char buffer[80] = {0};

	time(&raw_time);

	info = localtime(&raw_time);
	printf("当前时间是 %s", asctime(info));
	printf("%d-%d-%d %d-%d-%d \n", (info->tm_year + 1900), (info->tm_mon + 1),
		   info->tm_mday, info->tm_hour, info->tm_min, info->tm_sec);

	sprintf(buffer, "%d-%02d-%02d %02d-%02d-%02d.log", (info->tm_year + 1900), (info->tm_mon + 1),
			info->tm_mday, info->tm_hour, info->tm_min, info->tm_sec);
	printf("file name:%s \n", buffer);
	FILE *file_temp = fopen(buffer, "w");
	if (file_temp == NULL)
	{
		printf("create file failed \n");
	}
	else
	{
		fclose(file_temp);
	}

	return;
}

//atoi sscanf 函数测试
void func_24()
{
	int version = 0;
	char keyword[] = "data_version:";
	char test[] = "data_version:-234";
	uint8_t data[7] = {0};
	char test_2[] = "data:0x1234 0x22 0x33 0xdd 0xee 0xff";
	char keyword_2[] = "data:";

	version = atoi(&test[strlen(keyword)]);
	printf("字符串值 = %s, 整型值 = %d\n", test, version);

	sscanf(&test_2[strlen(keyword_2)], "%X %X %X %X %X %X %X",
		 &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6]);

	printf("data: %X, %X, %X, %X, %X, %X, %X",
		 data[0], data[1], data[2],data[3], data[4], data[5],data[6]);
	return;
}

//测试memcmp函数
void func_25()
{
	uint8_t data[7] = {0xAA, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0xaa};
	uint8_t decode_data[7] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0xaa};
	uint8_t result = 0;
	result = memcmp(data, decode_data, 7);
	printf("result:%d \n", result);
	if (memcmp(data, decode_data, 7) == 0) {
		printf("ok");
	} else {
		printf("not ok");
	}
}

//测试指针
//指针可以直接赋值
//结构体中的结构体指针只计算指针大小，而不是计算结构体大小
//所以初始化结构体时，其指针必须手动申请内存
#pragma pack(push)
#pragma pack(1)
typedef struct _a_t
{
	uint8_t a1;
	uint8_t a2;
	uint32_t a3;
} a_t;

typedef struct _test_t
{
	a_t *a;
	uint8_t b;
	uint32_t c;
} test_t;

void func_26()
{
	uint8_t *ptr_1 = NULL;
	uint32_t *ptr_2 = NULL;
	uint8_t dummy = 0xff;
	printf("1 ptr_1:%p, ptr_2:%p \n", ptr_1, ptr_2);
	ptr_1 = malloc(10);
	// memcpy(ptr_1, &dummy, 10);
	memset(ptr_1, 0xff, 10);
	ptr_2 = (uint32_t *)ptr_1;
	printf("2 ptr_1:%p, ptr_2:%p \n", ptr_1, ptr_2);
	free(ptr_1);

	uint32_t size_a_t = sizeof(a_t);
	uint32_t size_test_t = sizeof(test_t);
	printf("a_t size:%d, test_t size:%d \n", size_a_t, size_test_t);
}
#pragma pack(pop)

//测试传递函数指针
//传递函数名即可
typedef void (*test_func_t)(uint8_t a, uint8_t b);
void func_27_1(uint8_t a, uint8_t b)
{
	printf("enter %s\n", __FUNCTION__);
	printf("%s, a:%d, b:%d \n", __FUNCTION__, a, b);
	return;
}

void func_27_2(test_func_t func, uint8_t **ptr)
{
	printf("enter %s\n", __FUNCTION__);
	uint8_t *temp_ptr = NULL;
	uint8_t a = 1, b = 2;
	func(a, b);
	temp_ptr = malloc(4);
	printf("222 temp ptr:%p\n", temp_ptr);
	*ptr = temp_ptr;
	return;
}

void func_27()
{
	uint8_t *ptr_temp = NULL;
	printf("enter %s\n", __FUNCTION__);
	printf("111 ptr:%p\n",ptr_temp);
	func_27_2(func_27_1, &ptr_temp);
	printf("333 ptr:%p\n",ptr_temp);
	return;
}

//类似与 i++ i--等代码，都需要等待所在逻辑执行完成之后才会自增自减
void func_28()
{
	uint8_t buffer[10] = {0};
	uint8_t i = 0;
	buffer[i++] = 1;

	printf("i:%d, buffer: ", i);
	for (uint8_t j = 0; j < 10; j++) {
		printf("%d, ", buffer[j]);
	}
	printf("\n");
}

//测试宏转为结构体
/* define partition properties, see mtd_authority_t */
#define AUTH_RW_NONE        0
#define AUTH_READ_ONLY      1
#define AUTH_WRITE_ONLY     2
#define AUTH_RW_ALL         3
#define FLASH_LAYOUT_2M \
    { \
        0x0002, \
        0x00200000, \
        { \
            {0x00000000, 0x00008000, AUTH_RW_NONE}, \
            {0x00008000, 0x00008000, AUTH_RW_NONE}, \
            {0x00010000, 0x00001000, AUTH_RW_ALL}, \
            {0x00011000, 0x00001000, AUTH_RW_ALL}, \
            {0x00012000, 0x00006000, AUTH_RW_ALL}, \
            {0x00018000, 0x00001000, AUTH_RW_ALL}, \
            {0x00019000, 0x00006000, AUTH_RW_ALL}, \
            {0x0001F000, 0x00001000, AUTH_RW_ALL}, \
            {0x00020000, 0x000E0000, AUTH_RW_ALL}, \
            {0x00100000, 0x00070000, AUTH_RW_ALL}, \
            {0x00170000, 0x00070000, AUTH_RW_ALL}, \
            {0x001E0000, 0x0001E000, AUTH_RW_ALL}, \
            {0x001F0000, 0x00000000, AUTH_RW_NONE}, \
            {0x001F7000, 0x00000000, AUTH_RW_NONE}, \
            {0x001FE000, 0x00001000, AUTH_RW_NONE}, \
            {0x001FF000, 0x00001000, AUTH_RW_ALL}, \
        }, \
    }
#define FLASH_LAYOUT_4M \
    { \
        0x0004, \
        0x00400000, \
        { \
            {0x00000000, 0x00008000, AUTH_RW_NONE}, \
            {0x00008000, 0x00008000, AUTH_RW_NONE}, \
            {0x00010000, 0x00001000, AUTH_RW_ALL}, \
            {0x00011000, 0x00001000, AUTH_RW_ALL}, \
            {0x00012000, 0x00007000, AUTH_RW_ALL}, \
            {0x00000000, 0x00000000, AUTH_RW_ALL}, \
            {0x00019000, 0x00007000, AUTH_RW_ALL}, \
            {0x00000000, 0x00000000, AUTH_RW_ALL}, \
            {0x00020000, 0x00160000, AUTH_RW_ALL}, \
            {0x00180000, 0x000B0000, AUTH_RW_ALL}, \
            {0x00230000, 0x000B0000, AUTH_RW_ALL}, \
            {0x002E0000, 0x00010000, AUTH_RW_ALL}, \
            {0x00000000, 0x00000000, AUTH_RW_NONE}, \
            {0x002F0000, 0x00010000, AUTH_RW_ALL}, \
            {0x00300000, 0x000FF000, AUTH_RW_ALL}, \
            {0x003FF000, 0x00010000, AUTH_RW_ALL}, \
        }, \
    }
#define FLASH_LAYOUT_4M_PSRAM \
    { \
        0x0005, \
        0x00400000, \
        { \
            {0x00000000, 0x00008000, AUTH_RW_NONE}, \
            {0x00008000, 0x00008000, AUTH_RW_NONE}, \
            {0x00010000, 0x00001000, AUTH_RW_ALL}, \
            {0x00011000, 0x00001000, AUTH_RW_ALL}, \
            {0x00012000, 0x00007000, AUTH_RW_ALL}, \
            {0x00019000, 0x00007000, AUTH_RW_ALL}, \
            {0x00020000, 0x000FA000, AUTH_RW_ALL}, \
            {0x0011A000, 0x00066000, AUTH_RW_ALL}, \
            {0x00180000, 0x000FA000, AUTH_RW_ALL}, \
            {0x00270000, 0x00066000, AUTH_RW_ALL}, \
            {0x002E0000, 0x00010000, AUTH_RW_ALL}, \
            {0x002F0000, 0x00010000, AUTH_RW_ALL}, \
            {0x00300000, 0x000FF000, AUTH_RW_ALL}, \
            {0x003FF000, 0x00010000, AUTH_RW_ALL}, \
        }, \
    }

#define FUNC_29_TYPEDEF_TEST	0

#if !FUNC_29_TYPEDEF_TEST
struct part_info_t {
    uint32_t offset;
    uint32_t size;
    uint32_t authority;
};
struct partition_table {
    uint32_t device_id;                     /* device ID */
    uint32_t size;                          /* total memory size */
    struct part_info_t part[16];  			/* partition parameters */
};

const static struct partition_table g_part_table[3] = {FLASH_LAYOUT_2M, FLASH_LAYOUT_4M, FLASH_LAYOUT_4M_PSRAM};

#else	//FUNC_29_TYPEDEF_TEST
typedef struct _part_info_t {
    uint32_t offset;
    uint32_t size;
    uint32_t authority;
} part_info_t;
typedef struct _partition_table_t {
    uint32_t device_id;                     /* device ID */
    uint32_t size;                          /* total memory size */
    part_info_t part[16];  			/* partition parameters */
} partition_table_t;
#endif	//FUNC_29_TYPEDEF_TEST

void func_29()
{
#if !FUNC_29_TYPEDEF_TEST
	// struct partition_table part[2] = {FLASH_LAYOUT_2M, FLASH_LAYOUT_4M_PSRAM};
	struct partition_table part[3] = {0};
	struct partition_table temp = FLASH_LAYOUT_2M;
	part[0] = temp;

	printf("2m get part id:%d, size:0x%08x\n", part[0].device_id, part[0].size);
	printf("2m sp part info: offset:0x%08x, size:0x%08x\n", part[0].part[0].offset, part[0].part[0].size);
	printf("2m cul part info: offset:0x%08x, size:0x%08x\r\n", part[0].part[13].offset, part[0].part[13].size);

	part[2] = g_part_table[2];
	printf("4m get part id:%d, size:0x%08x\n", part[1].device_id, part[1].size);
	printf("4m sp part info: offset:0x%08x, size:0x%08x\n", part[1].part[0].offset, part[1].part[0].size);
	printf("4m cul part info: offset:0x%08x, size:0x%08x\r\n", part[1].part[13].offset, part[1].part[13].size);

	memcpy(&part[3], &g_part_table[3], sizeof(g_part_table[3]));
	printf("4m psram get part id:%d, size:0x%08x\n", part[2].device_id, part[2].size);
	printf("4m psram sp part info: offset:0x%08x, size:0x%08x\n", part[2].part[0].offset, part[2].part[0].size);
	printf("4m psram cul part info: offset:0x%08x, size:0x%08x\r\n", part[2].part[13].offset, part[2].part[13].size);
#else	//FUNC_29_TYPEDEF_TEST
	partition_table_t test_table = {0};
	printf("get part id:%d, size:0x%08x\n", test_table.device_id, test_table.size);
	printf("sp part info: offset:0x%08x, size:0x%08x\n", test_table.part[0].offset, test_table.part[0].size);
	printf("cul part info: offset:0x%08x, size:0x%08x\r\n", test_table.part[13].offset, test_table.part[13].size);
	partition_table_t temp_table = FLASH_LAYOUT_2M;
	test_table = temp_table;
	printf("get part id:%d, size:0x%08x\n", test_table.device_id, test_table.size);
	printf("sp part info: offset:0x%08x, size:0x%08x\n", test_table.part[0].offset, test_table.part[0].size);
	printf("cul part info: offset:0x%08x, size:0x%08x\r\n", test_table.part[13].offset, test_table.part[13].size);
	// test_table = FLASH_LAYOUT_4M_PSRAM;
	// printf("get part id:%d, size:0x%08x\n", test_table.device_id, test_table.size);
	// printf("sp part info: offset:0x%08x, size:0x%08x\n", test_table.part[0].offset, test_table.part[0].size);
	// printf("cul part info: offset:0x%08x, size:0x%08x\r\n", test_table.part[13].offset, test_table.part[13].size);

#endif	//FUNC_29_TYPEDEF_TEST
}

//测试C语言预处理指令 #error
//结论：枚举变量不参与预编译流程
typedef enum {
	PART_NUM_MAX_E = 0,
} func_30_part_1m_t;

typedef enum {
	PART_NUM_2M_MAX_E = 1,
} func_30_part_2m_t;

typedef enum {
	PART_NUM_4M_MAX_E = 1,
} func_30_part_4m_t;

#define PART_NUM_MAX	PART_NUM_MAX_E
#define PART_NUM_2M_MAX	PART_NUM_2M_MAX_E
#define PART_NUM_4M_MAX	PART_NUM_4M_MAX_E

#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - (2 * (!(condition)))]))

void func_30()
{
	// func_30_part_1m_t test1;
	// func_30_part_2m_t test2;
	// func_30_part_4m_t test4;
#if PART_NUM_MAX_E
#warning "PART_NUM_MAX_E is 1"
#else
#warning "PART_NUM_MAX_E is 0"
#endif

#if PART_NUM_2M_MAX_E
#warning "PART_NUM_2M_MAX_E is 1"
#else
#warning "PART_NUM_2M_MAX_E is 0"
#endif

#if PART_NUM_4M_MAX_E
#warning "PART_NUM_4M_MAX_E is 1"
#else
#warning "PART_NUM_4M_MAX_E is 0"
#endif

#if PART_NUM_MAX
#warning "PART_NUM_MAX is 1"
#else
#warning "PART_NUM_MAX is 0"
#endif

#if PART_NUM_2M_MAX
#warning "PART_NUM_2M_MAX is 1"
#else
#warning "PART_NUM_2M_MAX is 0"
#endif

#if PART_NUM_4M_MAX
#warning "PART_NUM_4M_MAX is 1"
#else
#warning "PART_NUM_4M_MAX is 0"
#endif

	BUILD_BUG_ON((PART_NUM_2M_MAX >= PART_NUM_4M_MAX) && (PART_NUM_2M_MAX > PART_NUM_MAX));
// #if ((PART_NUM_2M_MAX == PART_NUM_4M_MAX) && (PART_NUM_2M_MAX > PART_NUM_MAX))
// #if ((PART_NUM_2M_MAX_E == PART_NUM_4M_MAX_E) && (PART_NUM_2M_MAX_E > PART_NUM_MAX_E))
// #if ((1 == 1) && (1 > 0))
// #error "logic is 1"
// #else
// #error "logic is 0"
// #endif

// 	if ((PART_NUM_2M_MAX == PART_NUM_4M_MAX) && (PART_NUM_2M_MAX > PART_NUM_MAX)) {
// 		#error "logic is 1"
// 	} else {
// 		#error "logic is 0"
// 	}

	printf("%s end\n", __FUNCTION__);
}

//不能使用##？
// void func_31()
// {
// #define func_31_1m_psram		0x11
// #define func_31_2m				0x22
// #define func_31_2m_psram		0x33
// #define func_31_4m				0x44
// #define func_31_4m_psram		0x55

// 	uint8_t flash_size = 1;
// 	uint8_t psram_size = 2;
// 	uint8_t test = 0;
// 	if (psram_size) {
// 		test = func_31_##flash_size##m_psram;
// 	} else {
// 		test = func_31_##flash_size##m;
// 	}
// 	printf("%s, test:%d\n", __FUNCTION__, test);
// }

void func_32()
{
	char test[10] = "111111111";
	uint8_t num = 0;

	printf("%s \n", test);

	for (uint8_t i = 0; i < 10; i++) {
		test[i] = 48 + i;
	}

	printf("%s \n", test);

	return;
}

void func_33(void)
{
    uint8_t func_33_test[5] = {1, 2, 3, 4, 5};
    uint8_t i = 0;
    uint8_t *ptr = func_33_test;

    for(i = 0; i < 5; i++) {
        printf("i: %d, old value:%d, ", i, func_33_test[i]);
        *ptr ^= 0x55;
        ptr++;
        printf("new value:%d \n", func_33_test[i]);
    }

    return;
}

/* 字节转换为bit流 */
 int func_34()
 {
    uint8_t data[6] = {0xaa, 0xe9, 0x55, 0x66, 0x88, 0x33};
    uint8_t curr_bit = 0;
    uint8_t *ptr = data;

    printf("bit steam:");
    for (uint8_t i = 0; i < 48; i++) {
        if ((i != 0) && ((i % 8) == 0)) {
            ptr++;
            printf("\n");
        }
        curr_bit = (*ptr & (0x80 >> (i % 8))) ? 1 : 0;
        printf("%d ", curr_bit);
    }
    printf("\n");
 }

/* 数组对称输出 */
int func_35()
{
    uint32_t data[] = {
        3756, 3761, 3766, 3772, 3777, 3782, 3787, 3792, 3797, 3802, 3807, 3812,
        3816, 3821, 3826, 3831, 3835, 3840, 3844, 3849, 3853, 3858, 3862, 3867,
        3871, 3875, 3880, 3884, 3888, 3892, 3896, 3900, 3904, 3908, 3912, 3916,
        3920, 3924, 3928, 3931, 3935, 3939, 3942, 3946, 3950, 3953, 3957, 3960,
        3963, 3967, 3970, 3973, 3976, 3980, 3983, 3986, 3989, 3992, 3995, 3998,
        4001, 4003, 4006, 4009, 4012, 4014, 4017, 4019, 4022, 4025, 4027, 4029,
        4032, 4034, 4036, 4039, 4041, 4043, 4045, 4047, 4049, 4051, 4053, 4055,
        4057, 4059, 4060, 4062, 4064, 4066, 4067, 4069, 4070, 4072, 4073, 4074,
        4076, 4077, 4078, 4080, 4081, 4082, 4083, 4084, 4085, 4086, 4087, 4088,
        4089, 4089, 4090, 4091, 4091, 4092, 4093, 4093, 4094, 4094, 4094, 4095,
        4095, 4095, 4096, 4096, 4096, 4096, 4096, 4096
    };

    uint32_t len = sizeof(data) / sizeof(data[0]);
    printf("arrg len:%d\n", len);
    for (uint32_t i = 0; i < len; i++) {
        if ((i != 0) && (i % 16 == 0)) {
            printf("\n");
        }
        printf("%d, ", data[i]);
    }
    printf("\n");
    for (uint32_t i = len; i > 0; i--) {
        if ((i != len) && (i % 16 == 0)) {
            printf("\n");
        }
        printf("%d, ", data[i - 1]);
    }
    printf("\n");
    return 0;
}

int main()
{
	func_35();
	getchar();
	return 0;
}
