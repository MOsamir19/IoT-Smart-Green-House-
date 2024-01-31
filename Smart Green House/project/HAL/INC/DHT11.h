/*
 * DHT11.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef DHT11_H_
#define DHT11_H_

#ifndef F_CPU
#define F_CPU	8000000UL
#endif

#include "util/delay.h"
#include "avr/io.h"
#include "stdio.h"
#include "bit_handle.h"
#include "data_types.h"

	/*Sensor*/
void	Start_Signal();
void	Response_signal();
INT_8U	Receive_data();

	/*Fan*/
void Fan_Init(void);
void Fan_On(void);
void Fan_Off(void);



#endif /* DHT11_H_ */