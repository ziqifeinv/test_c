//结论，static修饰的函数仅限于本文件使用

#include <iostream>

#include "user_print.h"

//extern void user_print();

int main()
{
	std::cout << "这是main函数打印" << std::endl;
	user_print();
	getchar();
	return 0;
}