
//

#include <stdio.h>
#include <string.h>

int test1[3] = { 1,2,3,};

void test_func()
{
	int test2[3] = { 4,5,6 };
}

int main()
{
	int test3[3] = { 0 };
	memcpy(test3, test1, sizeof(test1));
	printf("test3 is :");
	for (int i = 0; i < 3; i++)
	{
		printf("%d,", test3[i]);
	}
	
	getchar();
	return 0;
}