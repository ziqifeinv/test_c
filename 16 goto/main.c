
#include "stdio.h"

void user_print(int counter)
{
	if (counter == 1) {
		goto u_print_1;
	}
	else if (counter == 2) {
		goto u_print_2;
	}
	else {
		goto u_print_3;
	}
	printf("if else over \n");

u_print_1:
	printf("input: 1 \n");
u_print_2:
	printf("input: 2 \n");
u_print_3:
	printf("input: 3 \n");
}

int main()
{
	user_print(1);
	getchar();
	return 1;
}