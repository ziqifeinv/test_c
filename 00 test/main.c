
#include <stdio.h>

int main()
{
	char test = 0;
	test = test ^ 3 ^ 4 ^ 5;
	printf("test is %d", test);
#if 0
	printf("ʮ���ƣ� %d\n", 256);
	printf("16���ƣ� %x\n", 256);
#endif
	getchar();
	return 0;
}