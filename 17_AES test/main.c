
#include <stdio.h>
#include <string.h>

typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;
struct _ge_data
{
	uint8_t data[3];
	uint8_t* prt[0];
};

extern int tiny_main(void);

void func_copy_test()
{
	struct _ge_data ge_data;
	uint8_t data[3] = { 0xab,0xcd,0xef };
	/*for (uint32_t i = 0; i < 3; i++)
	{
		ge_data.prt[i]= data[i];
	}*/

	memcpy(ge_data.prt, data, sizeof(data));

	//ge_data.prt[0] = data;

	for (uint32_t i = 0; i < 3; i++)
	{
		printf("%x ", ge_data.prt[i]);
	}
}

int main()
{
	//tiny_main();
	getchar();
	return 0;
}