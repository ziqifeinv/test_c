#include <iostream>
#include "user_struct.h"

typedef struct _iot_oem_cfg
{
	long board_cfg_num;
} iot_oem_cfg_t;

iot_oem_cfg_t oemcfg = { 2 };

board_info g_board_info = { 0 };

//g_board_info.board_id = oemcfg.board_cfg_oem;
