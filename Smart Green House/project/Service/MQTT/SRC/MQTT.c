/*
 * MQTT.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "MQTT.h"

const INT_8U proName[] = "MQTT";
INT_16U  packetidentifier = 1;

void MQTT_Init(void)
{
	UART_Init(UART_0,9600);
}
void MQTT_connect(INT_8U* pu8ID)
{
	INT_8U remLen = (2 + strlen(proName)) + 1 + 1 + 2 + (2 + strlen(pu8ID));
		/*   Wifi sending data command    */
	Wifi_Sendex_Command(remLen + 2);   
	
	UART_SendByte(UART_0,0x10);    /* packet type  */
	UART_SendByte(UART_0,remLen);  /*   Rem len    */
    encodeUTFstr(proName);         /*  pro name    */
	UART_SendByte(UART_0,0x04);    /*  pro level    */
	UART_SendByte(UART_0,0x02);    /*    flags     */
	UART_SendByte(UART_0,0xFF);    /*    KAT MSB   */
	UART_SendByte(UART_0,0xFF);    /*    KAT LSB   */
	encodeUTFstr(pu8ID);           /*   client ID  */
	UART_SendString(UART_0,"\r\n");
	
}

void MQTT_subscribe(INT_8U* topic)
{
	INT_8U remlen = 2 + (2 + strlen(topic)) + 1;
	Wifi_Sendex_Command(remlen + 2);				/*   Wifi sending data command    */
	UART_SendByte(UART_0,0x82);						/* packet type */
	UART_SendByte(UART_0,remlen);					/* remaining length */
	UART_SendByte(UART_0,packetidentifier >> 8);	/* packet ident  MSB */ 
	UART_SendByte(UART_0,packetidentifier);			/* pack identifier LSB */
	packetidentifier++;								/* sequence number */
	encodeUTFstr(topic);							/*  topic name */
	UART_SendByte(UART_0,0x01);						/* req. Qos  */
	UART_SendString(UART_0,"\r\n");	
}

void MQTT_publish(INT_8U* topic, INT_8U* pu8msg , INT_8U msgsize, INT_8U QOS)
{
	INT_8U remlen = 2 + strlen(topic) + msgsize;
	Wifi_Sendex_Command(remlen + 3);			/*  Wifi sending data command    */
	switch (QOS)
	{
		case 0: 
		UART_SendByte(UART_0,0x30);
		break;
		case 1 :
		UART_SendByte(UART_0,0x32);
		remlen = remlen + 2;
		break;
	}
	
	UART_SendByte(UART_0,remlen);
	
	encodeUTFstr(topic);
	if( QOS == 1)
	{
		UART_SendByte(UART_0,(packetidentifier>>8));
		UART_SendByte(UART_0,packetidentifier);
		packetidentifier++;
	}
	for (INT_8U count = 0; count <msgsize ; count++)
	{
		UART_SendByte(UART_0,pu8msg[count]);
	}
	UART_SendString(UART_0,"\\0\r\n");
		
}

void encodeUTFstr(INT_8U* str)
{
	UART_SendByte(UART_0, 0x00);          /* Len high byte  */
	UART_SendByte(UART_0, strlen(str));   /* Len low byte   */
	UART_SendString(UART_0,str);
}

void MQTT_Ping(void)
{
	Wifi_Sendex_Command(2);
	UART_SendByte(UART_0,0xC0);
	UART_SendByte(UART_0,0x00);
	UART_SendString(UART_0,"\r\n");	
}
