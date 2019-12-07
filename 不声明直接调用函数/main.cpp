//结论：函数的声明隐含了extern。

#include <iostream>
//#include "user_print.h"

void user_print();

void main()
{
	std::cout << "这是main打印的数据！" << std::endl;
	user_print();
	getchar();
}