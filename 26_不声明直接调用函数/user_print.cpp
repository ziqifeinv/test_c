#include <iostream>
#include "user_print.h"

char user_data[] = "这是user_print函数打印的数据！";

void user_print()
{
	std::cout << user_data << std::endl;
}