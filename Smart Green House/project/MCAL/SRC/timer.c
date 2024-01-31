/*
 * timer.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 
#include "timer.h"

volatile static INT_32U OverFlows = 0 ;
volatile static INT_32U CalcOverFlows = 0 ;

void (*volatile notifier)(void);

volatile static INT_32U notifiertime = 0;
 
void Timer0_Init(INT_8U mode)
{
	switch(mode)
	{
		case MODE_NORMAL:
		  CLEARBIT(TCCR0,WGM00);
		  CLEARBIT(TCCR0,WGM01);
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
		  SETBIT(TCCR0,WGM00);
		  SETBIT(TCCR0,WGM01);
     		  /* clear OC0 on compare, set Oc0 at bottom  */
  		  CLEARBIT(TCCR0,COM00);
		  SETBIT(TCCR0,COM01);
		break;
		case MODE_PHASE_PWM:
		  SETBIT(TCCR0,WGM00);
		  CLEARBIT(TCCR0,WGM01);
		    /* clear OC0 on compare, set Oc0 at bottom */
		  CLEARBIT(TCCR0,COM00);
		  SETBIT(TCCR0,COM01);
		break;
	}
	Timer0_Stop();
	
	
}
void Timer0_Start(void)
{
	/* prescaler = 8  */
	CLEARBIT(TCCR0,CS00);
	SETBIT(TCCR0,CS01);
	CLEARBIT(TCCR0,CS02);
}
void Timer0_Stop(void)
{
	CLEARBIT(TCCR0,CS00);
	CLEARBIT(TCCR0,CS01);
	CLEARBIT(TCCR0,CS02);
	
}

void Timer0_ResetCounters(void)
{
	TCNT0 = 0;
	OverFlows = 0;
}

void Timer0_DelayUS(INT_32U delayUS)
{
	Timer0_ResetCounters();
	Timer0_Start();
	while ((delayUS) > (TCNT0 + OverFlows*256 +1 ));
	
}
void Timer0_DelayMS(INT_32U delayMS)
{
	Timer0_ResetCounters();
	Timer0_Start();
	while ((delayMS * 1000UL) > (TCNT0 + OverFlows*256 +1 ));
}

/*          duty in range 0:100           */
void Timer0_SetDuty(INT_8U duty)
{
	OCR0 = (duty*255UL)/100;
}

/*        for adjusting duty cycle        */
void Timer0_IncDuty(INT_8U incDuty)
{
	if ((OCR0 + (incDuty*255UL)/100)<=255)
	{
		OCR0 += (incDuty*255UL)/100;
	}
	else 
	{
		OCR0 = 255;
	}
}
void Timer0_DecDuty(INT_8U decDuty)
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
void Timer0_SetNotification(void (*ptrFun)(void) ,INT_32U notifyDelay)
{
	notifier = ptrFun;
	notifiertime = notifyDelay;
	Timer0_ResetCounters();
	//calc counters
	TCNT0 = 256 - ((notifyDelay*1000)%256 - 1);
	CalcOverFlows = ((notifyDelay*1000)/256 + 1);
	Timer0_Start();
}


ISR(TIMER0_OVF_vect)
{
	OverFlows++;
	
if(OverFlows==CalcOverFlows)
{
	notifier();
	OverFlows = 0;
	TCNT0 = 256 - ((notifiertime*1000)%256 - 1);
}
}