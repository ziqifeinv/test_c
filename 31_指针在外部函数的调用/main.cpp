//结论：能在外部文件作为参数调用指针

#include <iostream>
#include "user_func.h"

extern void user_func(iot_ftm_event * value);

iot_ftm_event g_event = { 0 };
int main()
{
	iot_ftm_event* event = &g_event;
	std::cout << event << std::endl;
	std::cout << &event << std::endl;
	std::cout << "this is main print: " << g_event.data << std::endl;

	user_func(event);
	std::cout << "this is user_func print: " << g_event.data << std::endl;
	getchar();
	return 0;
}