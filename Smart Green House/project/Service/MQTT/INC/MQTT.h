/*
 * MQTT.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef MQTT_H_
#define MQTT_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "bit_handle.h"
#include "data_types.h"
#include "util/delay.h"
#include "UART.h"

void MQTT_Init(void);
void MQTT_connect(INT_8U* pu8ID);
void MQTT_subscribe(INT_8U* topic);
void MQTT_publish(INT_8U* topic, INT_8U* pu8msg , INT_8U msgsize, INT_8U QOS);
void encodeUTFstr(INT_8U* str);
void MQTT_Ping(void);




#endif /* MQTT_H_ */