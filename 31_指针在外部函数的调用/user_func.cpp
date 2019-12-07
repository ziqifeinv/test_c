
#include <iostream>
#include "user_func.h"

void user_func(iot_ftm_event* value)
{
	value->data[0] = 't';
	value->data[1] = 'a';
	value->data[2] = 'n';
}