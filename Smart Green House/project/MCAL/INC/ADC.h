/*
 * ADC.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef ADC_H_
#define ADC_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"
#include "util/delay.h"

typedef enum
{
	
	channel_1,
	channel_2,
	channel_3,
	channel_4,
	channel_5,
	channel_6,
	channel_7,
	channel_8
	
}ADC_CHANNEL;

typedef struct {
	INT_8U  MUX       :5;
	INT_8U  ADLAR_B   :1;
	INT_8U  REFS      :2;
	 
	}ADCMUX_BITFD;
	
typedef struct {
	INT_8U  ADPS      :3;
	INT_8U  ADIE_B    :1;
	INT_8U  ADIF_B    :1;
	INT_8U  ADFR_B    :1;
	INT_8U  ADSC_B    :1;
	INT_8U  ADEN_B    :1;
	
}ADCSRA_BITFD;


typedef struct {
	INT_16U            ADC_Data;
	ADCSRA_BITFD       ADCSRA_BF;
	ADCMUX_BITFD       ADCMUX_BF;
}ADC_Struct_BITFD;

#define    ADC_struct     (((volatile  ADC_Struct_BITFD*)(0x24)))

/*==============mapping everysingle register==================#define	ADC_Data_LR	(((volatile INT8U*)(0x24)))              |=#define	ADC_Data_HR	(((volatile INT8U*)(0x25)))              |=#define	ADC_Data_R	(((volatile INT16U*)(0x24)))             |=         #define	ADC_Data_R	(((volatile INT16U*)(0x24)))             |=#define	ADCMUX_BFR	(((volatile ADCMUX_BFD*)(0x27)))         |=#define	ADCSRA_BFR	(((volatile ADCSRA_BFD*)(0x26)))         |=
==============================================================
*/

void ADC_INIT(void);
INT_16U ADC_Read (INT_8U u8channel);
uint8_t* ADC_READ_FLOAT(INT_8U u8channel);




#endif /* ADC_H_ */