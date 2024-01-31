/*
 * timer3.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "timer3.h"

volatile static INT_32U OverFlows = 0 ;
volatile static INT_32U CalcOverFlows = 0 ;

void (*volatile notifier)(void);

volatile static INT_32U notifiertime = 0;
 
void Timer3_Init(INT_8U mode)
{
	SETBIT(DDRE,PE3);
	switch(mode)
	{
		case MODE_NORMAL:
		  CLEARBIT(TCCR3A,WGM00);
		  CLEARBIT(TCCR3A,WGM01);
		  SETBIT(TIMSK,TOIE0);  //enable overflow interrupt 
		break;
		case MODE_CTC:
		  CLEARBIT(TCCR0,WGM00);
		  SETBIT(TCCR0,WGM01);
		  /* toggle OC0 pin */
		  SETBIT(TCCR0,COM00);
		  CLEARBIT(TCCR0,COM01);
		break;
		case MODE_FAST_PWM:
		  CLEARBIT(TCCR3A,WGM30);
		  SETBIT(TCCR3A,WGM31);
     		  /* clear OC0 on compare, set Oc0 at bottom  */
  		  CLEARBIT(TCCR3A,COM3A0);
		  SETBIT(TCCR3A,COM3A1);
		  SETBIT(TCCR3B,WGM32);
		  SETBIT(TCCR3B,WGM33);
		  ICR3 = 255;
		break;
		case MODE_PHASE_PWM:
		  SETBIT(TCCR0,WGM00);
		  CLEARBIT(TCCR0,WGM01);
		    /* clear OC0 on compare, set Oc0 at bottom */
		  CLEARBIT(TCCR0,COM00);
		  SETBIT(TCCR0,COM01);
		break;
	}
	Timer3_Stop();
	
	
}
void Timer3_Start(void)
{
	/* prescaler = 8  */
	CLEARBIT(TCCR3B,CS30);
	SETBIT(TCCR3B,CS31);
	CLEARBIT(TCCR3B,CS32);
}
void Timer3_Stop(void)
{
	CLEARBIT(TCCR3B,CS30);
	CLEARBIT(TCCR3B,CS31);
	CLEARBIT(TCCR3B,CS32);
	
}

void Timer3_ResetCounters(void)
{
	TCNT3 = 0;
	OverFlows = 0;
}

void Timer3_DelayUS(INT_32U delayUS)
{
	Timer3_ResetCounters();
	Timer3_Start();
	while ((delayUS) > (TCNT3 + OverFlows*65535 +1 ));
	
}
void Timer3_DelayMS(INT_32U delayMS)
{
	Timer3_ResetCounters();
	Timer3_Start();
	while ((delayMS * 1000UL) > (TCNT3+ OverFlows*255 +1 ));
}

/*          duty in range 0:100           */
void Timer3_SetDuty(INT_8U duty)
{
	OCR3A = (duty*255UL)/100;
}

/*        for adjusting duty cycle        */
void Timer3_IncDuty(INT_8U incDuty)
{
	if ((OCR3A + (incDuty*255UL)/100)<=255)
	{
		OCR3A += (incDuty*255UL)/100;
	}
	else 
	{
		OCR3A = 255;
	}
}
void Timer3_DecDuty(INT_8U decDuty)
{
	if (OCR0 >= (decDuty*255UL)/100)
	{
		OCR0 -= (decDuty*255UL)/100;
	}
	else
	{
		OCR0 = 0;
	}
}

/*    send any notification after delay   */
void Timer3_SetNotification(void (*ptrFun)(void) ,INT_32U notifyDelay)
{
	notifier = ptrFun;
	notifiertime = notifyDelay;
	Timer3_ResetCounters();
	//calc counters
	TCNT0 = 256 - ((notifyDelay*1000)%256 - 1);
	CalcOverFlows = ((notifyDelay*1000)/256 + 1);
	Timer3_Start();
}


ISR(TIMER3_OVF_vect)
{
	OverFlows++;
	
if(OverFlows==CalcOverFlows)
{
	notifier();
	OverFlows = 0;
	TCNT0 = 256 - ((notifiertime*1000)%256 - 1);
}
}