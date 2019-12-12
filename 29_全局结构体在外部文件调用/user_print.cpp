#include <iostream>
#include "user_struct.h"

extern board_info g_board_info;

void user_print()
{
	g_board_info.board_id = 2;
	std::cout << g_board_info.board_id << std::endl;
}