/*
 * App.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef APP_H_
#define APP_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

		/* include needed header files*/
#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#include "bit_handle.h"
#include "data_types.h"
#include "util/delay.h"
#include "avr/interrupt.h"

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
#include "MQTT.h"
#include "Board.h"
#include "ADC.h"
#include "LDR.h"
#include "DHT11.h"
#include "SOIL_MOISTURE.h"
#include "Wifi.h"
#include "timer.h"
#include "LCD4bit.h"

	/* Event Group Bits*/
#define      E_MQTT_PUBACK        (1<<0)
#define      E_MQTT_SUBACK        (1<<1)
#define      E_MQTT_CONNACK       (1<<2)
#define      WiFi_ACK             (1<<3)
#define      E_MQTT_PINGREQ       (1<<4)
#define      LCDreadings_Disp1     "Temp=     SM=   "
#define      LCDreadings_Disp2     "Hum=      L=    "

extern INT_8U system_up;

void T_Control(void* pvData);
void T_Monitor(void* pvData);
void T_RespHandle(void* pvData);
void T_Connect(void* pvData);
void T_Self_Control(void* pvData);
void System_Init(void);
void DHT_Monitor(void);

#endif /* APP_H_ */