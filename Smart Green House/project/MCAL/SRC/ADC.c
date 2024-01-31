
/*
 * ADC.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "ADC.h"
#include "LCD4bit.h"

void ADC_INIT(void)
{
	/*  clock       */
	ADC_struct->ADCSRA_BF.ADPS = 0b111;
	/*  ref->  AVCC */
	ADC_struct->ADCMUX_BF.REFS = 0b01;
	/*  Enable      */  
	ADC_struct->ADCSRA_BF.ADEN_B = 1;
	
}

INT_16U ADC_Read (INT_8U u8channel)
{
	//   =========select channel=============
	ADC_struct->ADCMUX_BF.MUX = u8channel;
	//   =========start conversion===========
	ADC_struct->ADCSRA_BF.ADSC_B = 1;
	//   ===wait until conversion completes==
	while(ADC_struct->ADCSRA_BF.ADSC_B == 1);  
	//   =========return ADC data============
	return ADC_struct->ADC_Data;
}

uint8_t* ADC_READ_FLOAT(INT_8U u8channel)
{
	uint16_t digitaldata= ADC_Read(u8channel);
	float  FLOATData=0.0;
	FLOATData=(float)(digitaldata*5)/1023;
	return (float_to_ascii(FLOATData));

}
