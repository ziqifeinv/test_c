#include "3.h"
#include <stdio.h>

test_t test_value;

int main()
{
	test_value.b = 3;
	test_value.a.x = 5;
	printf("%d,%d", test_value.a.x, test_value.b);
	getchar();
}