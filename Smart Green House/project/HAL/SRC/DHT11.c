/*
 * DHT11.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "DHT11.h"
#include "Project_Config.h"
INT_8U data_byte	=	0;

void Start_Signal()
{
		/*Set as O/P */
	SETBIT(DHT11_DDR,DHT11_Data);
		/* Free status HIGH */
	SETBIT(DHT11_PORT,DHT11_Data);
	_delay_ms(1);
	/*Start Start Signal*/
	CLEARBIT(DHT11_PORT,DHT11_Data);
	_delay_ms(20);
	SETBIT(DHT11_PORT,DHT11_Data);
}

void Response_Signal()
{
		/*Set as I/P */
	CLEARBIT(DHT11_DDR,DHT11_Data);
	while(	readbit(DHT11_PIN,DHT11_Data)); 
	/* Wait for DHT LOW response signal*/
	while(! readbit(DHT11_PIN,DHT11_Data));	
	/* Wait for DHT HIGH response signal*/
	while(  readbit(DHT11_PIN,DHT11_Data));  
}

INT_8U Receive_data()
{
	for (INT_8U i=0; i<8; i++)
	{
		while(readbit(DHT11_PIN,DHT11_Data)==0);
		_delay_us(30);
		if(readbit(DHT11_PIN,DHT11_Data))
		{
			SETBIT(data_byte,(7-i));
		}
		else
		{
			CLEARBIT(data_byte,(7-i));
		}
		while(readbit(DHT11_PIN,DHT11_Data));
	}
	return data_byte;
}
void Fan_Init(void)
{   /* out */
	SETBIT(Fan_DDR,Fan_PIN_Number);
	/* Fan off */
	Fan_Off();
}
void Fan_On(void)
{
	/* high */
	SETBIT(Fan_PORT,Fan_PIN_Number);
}
void Fan_Off(void)
{
	/* low */
	CLEARBIT(Fan_PORT,Fan_PIN_Number);
}