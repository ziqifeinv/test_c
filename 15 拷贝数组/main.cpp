
//内存相关函数均以byte为单位操作

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define data_len	5

uint32_t test1[data_len] = { 0xaaaaaaaa ,0xbbbbbbbb ,0xcccccccc, 0xdddddddd, 0xeeeeeeee };

int main()
{
	uint32_t test2[data_len] = { 0 };
	uint8_t test3[data_len * 4] = { 0 };
	memcpy(test3, test1, data_len * 4);

	printf("test3 len:%d \n", sizeof(test3));
	printf("test3 is :");
	for (int i = 0; i < data_len * 4; i++)
	{
		printf("%X,", test3[i]);
	}
	printf("\n");

	printf("test2 len:%d \n", sizeof(test2));
	memcpy(test2, test3, data_len*4);
	printf("test2 is :");
	for (int i = 0; i < data_len; i++)
	{
		printf("%X,", test2[i]);
	}
	printf("\n");
	
	memset(test2, 0, data_len * 4);
	printf("test2 set 0is :");
	for (int i = 0; i < data_len; i++)
	{
		printf("%X,", test2[i]);
	}
	printf("\n");

	memcpy(test2, test1, data_len * 4);
	printf("test2 is :");
	for (int i = 0; i < data_len; i++)
	{
		printf("%X,", test2[i]);
	}
	printf("\n");

	getchar();
	return 0;
}