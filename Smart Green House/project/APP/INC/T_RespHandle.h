/*
 * T_RespHandle.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef T_RESPHANDLE_H_
#define T_RESPHANDLE_H_

#include "App.h"

extern xSemaphoreHandle     bsConnect;
extern xQueueHandle         mqControl;
extern xQueueHandle         UARTcontrol;
extern EventGroupHandle_t   egMQTT;
extern EventBits_t          ebValuesMQTT;
extern Bool                 Wifi_Connecting;

typedef enum {
	RS_NONE,RS_PackType,RS_Remaining
	}RecState;

#endif /* T_RESPHANDLE_H_ */