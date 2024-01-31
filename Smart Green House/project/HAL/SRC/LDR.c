/*
 * LDR.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 
#include "LDR.h"

void LDR_Init(void)
{
	ADC_INIT();
}
void LDR_Val (INT_16U* u16LDR_Value)
{
		/* Read adc value*/
    *u16LDR_Value=ADC_Read(LDR_channel); 
		/* Convert adc value to percentage*/
	*u16LDR_Value=( *u16LDR_Value /850.0)*100.0;
	
}