
/*
 * Dim_LED.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "Dim_LED.h"
#include "board.h"

void Dim_LED_Init (void)
{
	Timer3_Init(MODE_FAST_PWM);
	SETBIT(DDRE,PE3);
	Dim_LED_Brightness(100);
}


void Dim_LED_Brightness (INT_8U Duty)
{
	Timer3_Start();
	Timer3_SetDuty(Duty);
}
void Dim_LED_Stop (void)
{
	Timer3_SetDuty(0);
	_delay_ms(1);
	Timer3_Stop();
	
	
}