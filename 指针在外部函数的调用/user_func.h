#pragma once
#include <iostream>

typedef struct _iot_ftm_event {
	uint16_t event_id;
	uint8_t data[0];
}iot_ftm_event;