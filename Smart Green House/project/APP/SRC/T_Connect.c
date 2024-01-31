
/*
 * T_Connect.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "T_Connect.h"

INT_8U system_up;
Bool Wifi_Connecting = TRUE ; 

void T_Connect(void* pvData)
{
	EventBits_t ebValues = 0;
	Wifi_EchoMode(NoEcho);
	vTaskDelay(500);
	Wifi_Connecting = FALSE;
	vTaskDelay(500);
	Wifi_AP_Connect((INT_8U*)"etsh",(INT_8U*)"01001225199619");
	ebValues = xEventGroupWaitBits(egMQTT,WiFi_ACK,1,0,10000);
	if(ebValues&WiFi_ACK)
	{
		LCD_DispStrXY(1,1,(INT_8U*)"WiFi connected ");
		Wifi_Connecting = TRUE ;
	}else
	{
		LCD_DispStrXY(1,1,(INT_8U*)"WiFi failed");
		while(1);
	}
	vTaskDelay(1000);
	Wifi_ConnectionMode(single);
	vTaskDelay(1000);
	
	while(1)
	{
		/*  wait for disconnection */
		if(xSemaphoreTake(bsConnect,portMAX_DELAY))
		{
			Wifi_Connecting = FALSE;
			Wifi_StartTCP_Conn((INT_8U*)"broker.hivemq.com",(INT_8U*)"1883",(INT_8U*)"10");
			ebValues = xEventGroupWaitBits(egMQTT,WiFi_ACK,1,0,4000);
			if(ebValues&WiFi_ACK)
			{
				LCD_DispStrXY(2,1,(INT_8U*)"Server connected ");
				Wifi_Connecting = TRUE;
				
			}else
			{
				LCD_DispStrXY(2,1,(INT_8U*)"Server failed");
			}
			vTaskDelay(1000);
			/* Connect  */
			MQTT_connect("Fedaa");
			/*wait CONNACK*/
			ebValues = xEventGroupWaitBits(egMQTT,E_MQTT_CONNACK,1,0,5000);
			if(ebValues&E_MQTT_CONNACK)
			{
				/* Connect done */
				vTaskDelay(1000);
				/*subscribe */
				MQTT_subscribe("SGH_control2020");
				/* suback */
				ebValues = xEventGroupWaitBits(egMQTT,E_MQTT_SUBACK,1,0,5000);
				if(ebValues&E_MQTT_SUBACK)
				{
					/* subscribe done */
					system_up = 1 ;	
					LCD_DispStrXY(1,1,LCDreadings_Disp1);
					LCD_DispStrXY(2,1,LCDreadings_Disp2);
					
				}else
				{
					xSemaphoreGive(bsConnect);
				
				}
				
			}else
			{
				xSemaphoreGive(bsConnect);
			}
		}
		
	}
	
}