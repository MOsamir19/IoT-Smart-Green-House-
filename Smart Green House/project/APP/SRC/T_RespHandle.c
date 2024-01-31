
/*
 * T_RespHandle.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "T_RespHandle.h"

static INT_8U recpacket[30];

void T_RespHandle(void* pvData)
{
	INT_8U u8Byte = 0;
	RecState recState = 0;
	INT_8U  recInd = 0;
	INT_8U  remLen = 0;
	while(1)
	{
		if(UART_RecieveByte_Unblocked(UART_0,&u8Byte))
		{
			switch(recState)
			{
				case RS_NONE:
				if(Wifi_Connecting == TRUE && u8Byte == 0x3A)
				{
					u8Byte = UART_Receive(UART_0);
					if (u8Byte == 0xD0)
					{
						xEventGroupSetBits(egMQTT,E_MQTT_PINGREQ);
					}
				if(u8Byte == 0x90||
				u8Byte == 0x20||
				u8Byte == 0x30||
				u8Byte == 0x40
				)
				{
					recpacket[0] = u8Byte;
					recState = RS_PackType;
					
				}
				}else if (Wifi_Connecting == FALSE)
				{
					if(u8Byte == 'O')
					{
						if(UART_Receive(UART_0)=='K')
						{
							xEventGroupSetBits(egMQTT,WiFi_ACK);
						}
					}
				}
					
					break;
					case RS_PackType:
					recpacket[1] = u8Byte;
					remLen = u8Byte;
					recInd = 0;
					recState = RS_Remaining;
					break;
					case RS_Remaining:
					recpacket[recInd + 2] = u8Byte;
					recInd++;
					if(recInd == remLen)
					{
						recState = RS_NONE;
						switch(recpacket[0])
						{
							case 0x30:
							xQueueSend(mqControl,recpacket,0);
							break;
							case 0x20:
							xEventGroupSetBits(egMQTT,E_MQTT_CONNACK);
							break;
							case 0x40:
							xEventGroupSetBits(egMQTT,E_MQTT_PUBACK);
							break;
							case 0x90:
							xEventGroupSetBits(egMQTT,E_MQTT_SUBACK);
							break;
						}
						
					}
					break;
				}
			}
			else vTaskDelay(2);
			
		}
		
	}