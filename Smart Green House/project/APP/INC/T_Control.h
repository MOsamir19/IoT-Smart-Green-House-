/*
 * T_Control.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef T_CONTROL_H_
#define T_CONTROL_H_
#include "App.h"
#include "string.h"


extern xSemaphoreHandle     bsConnect;
extern xQueueHandle         mqControl;
extern EventGroupHandle_t   egMQTT;
extern EventBits_t          ebValuesMQTT;
INT_8U SELF_CONTROL = 0;



#endif /* T_CONTROL_H_ */