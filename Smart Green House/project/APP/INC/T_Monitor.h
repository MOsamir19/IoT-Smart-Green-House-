/*
 * T_Monitor.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef T_MONITOR_H_
#define T_MONITOR_H_

#include "App.h"


extern xSemaphoreHandle     bsConnect;
extern xQueueHandle         mqControl;
extern xQueueHandle         DHTreadings;
extern EventGroupHandle_t   egMQTT;
extern EventBits_t          ebValuesMQTT;

extern  INT_8U   system_up;
extern	INT_8U	I_H ;
extern	INT_8U	D_H;
extern	INT_8U	I_Temp;
extern  INT_8U	D_Temp;
extern  INT_8U	CheckSum;

INT_16U light = 0;
INT_16U Soil_data = 0;

#endif /* T_MONITOR_H_ */