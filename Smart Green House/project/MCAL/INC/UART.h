/*
 * UART.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef UART_H_
#define UART_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"
#include "util/delay.h"
#include "avr/interrupt.h"


typedef enum {
	UART_0,UART_1
	}UART_TYPE;
	
	
	
void UART_Init(UART_TYPE uartNum , INT_32U u32Baud);

void UART_SendByte(UART_TYPE UartNum , INT_8U u8Data );
INT_8U UART_Receive(UART_TYPE UartNum);


void UART_SendString(UART_TYPE UartNum, INT_8U* pu8string);
// to check if their is data or not , if true data -> pu8data , if false return false
Bool UART_RecieveByte_Unblocked(UART_TYPE UartNum, INT_8U* pu8data);
void UART_CallSetup(UART_TYPE uartType, void (*ptr_CallBack_Fun)(void));







#endif /* UART_H_ */