
//结论：即使定义在函数内部，define定义的内容在同一个文件内仍然有效，且会出现重定义现象

#include <stdio.h>
#include "user_print.h"

#define test define_test

int user_print_3()
{
#define tanxiong 33
	printf("user_print_3 func:%d\n", tanxiong);
	return 0;
}

int user_print_4()
{
#define tanxiong 44
	printf("user_print_4 func:%d\n", tanxiong);
	return 0;
}

int main()
{
	user_print_1();
	printf("main func:%d\n", tanxiong);
	printf("main test:%d\n", test);
	getchar();
	return 0;
}

