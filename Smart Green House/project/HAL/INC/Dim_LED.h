/*
 * Dim_LED.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef DIM_LED_H_
#define DIM_LED_H_


#include "timer3.h"

void Dim_LED_Init (void);
void Dim_LED_Brightness (INT_8U Duty);
void Dim_LED_Stop (void);


#endif /* DIM_LED_H_ */