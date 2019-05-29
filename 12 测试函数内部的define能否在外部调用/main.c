
//结论：即使定义在函数内部，define定义的内容在同一个文件内仍然有效

#include <stdio.h>
#include "user_print.h"

int main()
{
	user_print();
	printf("main func:%d\n", tanxiong);
	getchar();
	return 0;
}

