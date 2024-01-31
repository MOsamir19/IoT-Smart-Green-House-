/*
 * Wifi.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */  
 
#include "Wifi.h"

/* WiFi configuration and modes */
void Wifi_Init(Config_Mode Configmode)
{
	UART_Init(UART_0,9600);
	
	switch(Configmode)
	{
		case Station:
			UART_SendString(UART_0,"AT+CWMODE_CUR=1\r\n");
		break;
		case AccessPoint:
			UART_SendString(UART_0,"AT+CWMODE_CUR=2\r\n");
		break;
		case Both_Sta_Ap:
			UART_SendString(UART_0,"AT+CWMODE_CUR=3\r\n");
		break;
	}
	_delay_ms(1000);
	
}
void Wifi_EchoMode(EchoMode echomode)
{
	switch(echomode)
	{
		case Echo:
			UART_SendString(UART_0,"ATE1\r\n");
		break;
		case NoEcho:
			UART_SendString(UART_0,"ATE0\r\n");
		break;
	}
}
void Wifi_AP_Connect(INT_8U* username, INT_8U* password)
{
	INT_8U str[50]= {'0'};
	sprintf(str,"AT+CWJAP_CUR=\"%s\",\"%s\"\r\n",username,password);
	UART_SendString(UART_0,str);	
}


/*  TCP/IP configurations */

void Wifi_ConnectionMode(Connection_TCPMode Connmode)
{
	switch (Connmode)
	{
		case single:
			UART_SendString(UART_0,"AT+CIPMUX=0\r\n");
		break;
		case multiple:
			UART_SendString(UART_0,"AT+CIPMUX=1\r\n");
		break;
	}
}
void Wifi_StartTCP_Conn(INT_8U* ipAdress, INT_8U* portNo , INT_8U* keepAlive)
{
	INT_8U str[50]={'0'};
	sprintf(str,"AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",ipAdress,portNo);
	UART_SendString(UART_0,str);
}

void Wifi_SendStr(INT_8U* pu8msg)
{
	UART_SendString(UART_0,"AT+CIPSENDEX=30");
	_delay_ms(500);
}

Bool Wifi_Expected_Response(INT_8U* pu8resp,INT_16U Expected_Timeout_ms)
{
	INT_8U Recieved_Response[100] = {'0'};
	INT_8U index = 0;
	INT_16U Timeout = 0;
	Bool result = FALSE;
	while(Timeout < Expected_Timeout_ms)
	{
		if(UART_RecieveByte_Unblocked(UART_0,&Recieved_Response[index]))
		{
			if (strstr(Recieved_Response,pu8resp))
			{
				result = TRUE;
				break;
			}
			index++;
		}else
		{
			_delay_ms(1);
			Timeout++;
		}
			
		
	}
	return result;
	
}

void Wifi_Sendex_Command(INT_8U length)
{
	
	INT_8U str[20]={'0'};
	sprintf(str,"AT+CIPSENDEX=%d\r\n",length);
	UART_SendString(UART_0,str);
	_delay_ms(300);
}

void Wifi_Stop_Sending(void)
{
	UART_SendString(UART_0,"\\0\r\n");	
}

Bool Wifi_Recieve_Byte_unblock(INT_8U* pu8data)
{
	return UART_RecieveByte_Unblocked(UART_0,pu8data);
}


INT_8U TCP_GetStatus(void)
{
	UART_SendString(UART_0,"AT+CIPSTATUS\r\n");
	Response Resp = WaitingForResponse;
	TCP_Error_code code = UnknownError;
	INT_8U index = 0;
	INT_8U data = 0;
	while(index < 12)
	{
		
		switch(Resp)
		{
			case WaitingForResponse:
			data = UART_Receive(UART_0);
			if (data == ':')
			{
				index = 0;
				data = UART_Receive(UART_0);
				Resp = Response_Recieved;
			}
			
			break;
			case Response_Recieved:

				if(data == '2')
				{
					code = Connection_Success;
					
				}else if(data == '3')
				{
					code = Connection_Created;
					
				}else if(data == '4')
				{
					code = Connection_fail;
					
				}else if(data == '5')
				{
					code = NoWifi_Connection;				
				}
			break;
		}
		index++;	
	}
	return code;
}