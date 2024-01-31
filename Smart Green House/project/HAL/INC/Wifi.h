
/*
 * Wifi.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */  
#ifndef WIFI_H_
#define WIFI_H_

#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"
#include "UART.h"
#include <string.h>


#ifndef F_CPU
#define F_CPU 8000000UL
#endif

typedef enum{
	NoEcho, Echo
	}EchoMode;

typedef enum{
	Station = 1,
	AccessPoint,
	Both_Sta_Ap
	}Config_Mode;
	
typedef enum{
	single,
	multiple
	}Connection_TCPMode;
	
typedef enum{
	Conn_Timeout = 1,
	Wrong_Pass,
	AP_NotFound,
	Conn_Failed
	}AP_Error_Code;
	
typedef enum{
	Connection_Success = 2,
	Connection_Created,
	Connection_fail,
	NoWifi_Connection,
	UnknownError
	}TCP_Error_code;
	
typedef enum{
	WaitingForResponse,
	Response_Recieved,
	}Response;

#define   Join_AP_succeeded      "WIFI CONNECTED"
#define   OK                     "OK"
#define   ERROR                  "ERROR"  
#define   DCHP_GotIP             "GOT IP"

/* WiFi configuration and modes */
void Wifi_Init(Config_Mode Configmode);
void Wifi_EchoMode(EchoMode echomode);
void Wifi_AP_Connect(INT_8U* username, INT_8U* password);
void Wifi_AP_Disconnect(void);
void Wifi_Restart(void);


/*  TCP/IP configurations */

void Wifi_ConnectionMode(Connection_TCPMode Connmode);
void Wifi_StartTCP_Conn(INT_8U* ipAdress, INT_8U* portNo , INT_8U* keepAlive);
void Wifi_SendStr(INT_8U* pu8msg);
void Wifi_StopTCP_Conn(void);
INT_8U TCP_GetStatus(void);
/* Data Transfer */
void Wifi_Send_FixedData(INT_8U* pu8Data, INT_16U length);
void Wifi_Send_VariableData(INT_8U* pu8Data, INT_16U Maxlength);
void Wifi_Sendex_Command(INT_8U length);
void Wifi_Stop_Sending(void);
INT_8U Wifi_Recieve_data(void);
Bool Wifi_Recieve_Byte_unblock(INT_8U* pu8data);

Bool Wifi_Expected_Response(INT_8U* pu8resp,INT_16U Expected_Timeout_ms);

#endif /* WIFI_H_ */