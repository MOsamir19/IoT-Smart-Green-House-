/*
 * UART.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "UART.h"

void (*ptr_CallList[2])(void);

void UART_Init(UART_TYPE uartNum , INT_32U u32Baud)
{
	/* calculate ubrr from baudrate */
	INT_32U ubrr = 0;
	ubrr = ((F_CPU)/(16*u32Baud)) - 1;
	
	switch(uartNum)
	{
		case UART_0:
		/*setting baudrate */
		UBRR0H = (INT_8U)(ubrr>>8);
		UBRR0L = (INT_8U)(ubrr);
		/* enable receive and transmitter*/
		UCSR0B = (1<<RXEN)| (1<<TXEN);
		/*set frame format : 8data, 1 stop */
		UCSR0C =(3<<UCSZ0);
		break;
		case UART_1:
		/*setting baudrate */
		UBRR1H = (INT_8U)(ubrr>>8);
		UBRR1L = (INT_8U)(ubrr);
		/* enable receive and transmitter*/
		UCSR1B = (1<<RXEN)| (1<<TXEN);
		/*set frame format : 8data, 1 stop */
		UCSR1C =(3<<UCSZ0);
		break;
	}
	
	
}

void UART_SendByte(UART_TYPE UartNum , INT_8U u8Data )
{
	switch(UartNum)
	{
		case UART_0:
		/* wait for empty transmit buffer*/
		while(!(UCSR0A & (1<<UDRE)));
		
		UDR0 = u8Data;
		break;
		case UART_1:
		
		while(!(UCSR1A & (1<<UDRE)));
		
		UDR1 = u8Data;
		break;
		
	}
}
INT_8U UART_Receive(UART_TYPE UartNum)
{
	uint8_t u8data =0;
	switch(UartNum)
	{
		case UART_0 :
		//wait for empty transmit buffer
		while(!(UCSR0A & (1 << RXC)));
		// put data into buffer, sends the data
		u8data = UDR0;
		break;
		case UART_1:
		//wait for empty transmit buffer
		while(!(UCSR1A & (1 << RXC)));
		// put data into buffer, sends the data
		u8data = UDR1;
		break;
		
	}
	return u8data;
	
}


void UART_SendString(UART_TYPE UartNum, INT_8U* pu8string)
{
	INT_32U ind = 0;
	while (pu8string[ind]!=0)
	{
		UART_SendByte(UartNum,pu8string[ind]);
		ind++;
	}
}
// to check if their is data or not , if true data -> pu8data , if false return false
Bool UART_RecieveByte_Unblocked(UART_TYPE UartNum, INT_8U* pu8data)
{
	Bool result = FALSE;
	switch(UartNum)
	{
		case UART_0:
		if(UCSR0A & (1<<RXC))
		{
			result = TRUE;
			*pu8data = UDR0;
		}
		break;
		case UART_1:
		if(UCSR1A & (1<<RXC))
		{
			result = TRUE;
			*pu8data = UDR1;
		}
		break;
		
	}
	return result;
}

void UART_CallSetup(UART_TYPE uartType, void (*ptr_CallBack_Fun)(void))
{
	switch(uartType)
	{
		case UART_0:
		SETBIT(UCSR0B,RXCIE);
		break;
		case UART_1:
		SETBIT(UCSR1B,RXCIE);
		break;
	}
	ptr_CallList[uartType]= ptr_CallBack_Fun;
}

ISR(USART0_RX_vect)
{
	ptr_CallList[UART_0]();
}

ISR(USART1_RX_vect)
{
	ptr_CallList[UART_1]();
	
}