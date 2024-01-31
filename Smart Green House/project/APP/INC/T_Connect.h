/*
 * T_Connect.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 
#ifndef T_CONNECT_H_
#define T_CONNECT_H_

#include "App.h"


extern xSemaphoreHandle     bsConnect;
extern xQueueHandle         mqControl;
extern EventGroupHandle_t   egMQTT;
extern EventBits_t          ebValuesMQTT;


#endif /* T_CONNECT_H_ */