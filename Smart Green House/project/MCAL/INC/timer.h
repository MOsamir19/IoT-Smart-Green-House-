/*
 * timer.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef TIMER_H_
#define TIMER_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"
#include "util/delay.h"
#include "avr/interrupt.h"


#define   MODE_NORMAL      0
#define   MODE_CTC         1
#define   MODE_FAST_PWM    2
#define   MODE_PHASE_PWM   3

void Timer0_Init(INT_8U mode);
void Timer0_Start(void); 
void Timer0_Stop(void);
void Timer0_ResetCounters(void);

void Timer0_DelayUS(INT_32U delayUS);
void Timer0_DelayMS(INT_32U delayMS);

/* duty in range 0:100 */
void Timer0_SetDuty(INT_8U duty);

/*  for adjusting duty cycle  */
void Timer0_IncDuty(INT_8U incDuty);
void Timer0_DecDuty(INT_8U decDuty);

/* send any notification after delay asynchronous (parallel with the main) */
void Timer0_SetNotification(void (*ptrFun)(void) ,INT_32U notifyDelay);


#endif /* TIMER_H_ */