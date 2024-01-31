/*
 * EXT_INTERRUPT.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"
#include "util/delay.h"
#include "avr/interrupt.h"

typedef enum{
	INT_NUM_0,INT_NUM_1,INT_NUM_2,INT_NUM_3
	}INT_NUM;
	
typedef enum{
	INT_STATE_FALLING,INT_STATE_RISING
}INT_STATE;

typedef enum{
	GLobal_closed,Global_open
	}GLobal_Int_state;

void EXT_Init(INT_NUM  intNUM, INT_STATE intSTATE);
void EXT_Disable(INT_NUM intNUM);
void EXT_CallSetup(INT_NUM intNUM, void (*ptr_CallBack_Fun)(void));
void GLobal_Int_Flag(GLobal_Int_state state);



#endif /* EXT_INTERRUPT_H_ */