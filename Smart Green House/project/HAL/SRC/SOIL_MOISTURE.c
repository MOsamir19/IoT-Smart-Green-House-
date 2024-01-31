/*
 * SOIL_MOISTURE.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */  

#include    "SOIL_MOISTURE.h"

void Soil_Moisture_Init(void)
{
	ADC_INIT();	
}

void Soil_Moisture_Read(INT_16U* COPY_u16Data)
{
		/* Read adc value*/
	*COPY_u16Data=ADC_Read(Soil_Moisture_channel);
		/* Convert adc value to percentage*/
	*COPY_u16Data=(  ((FP32)(*COPY_u16Data)/1000 ) *100 );
	
}

void Water_Pump_Init(void)
{
	SETBIT(Water_Pump_DDR,Water_Pump_PIN_Number);
	Water_Pump_OFF();
}


void Water_Pump_ON(void)
{
	SETBIT(Water_Pump_PORT,Water_Pump_PIN_Number);
}

void Water_Pump_OFF(void)
{
	CLEARBIT(Water_Pump_PORT,Water_Pump_PIN_Number);
}

/**********************************************************/