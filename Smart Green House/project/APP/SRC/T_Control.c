
/*
 * T_Control.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "T_Control.h"

static INT_8U cmdPacket[30];

void T_Control(void* pvData)
{
	INT_8U ind =0;
	char* ptrDol_Sign = NULL;
	char* ptrHash_Sign = NULL;
	INT_8U DataSize = 0;
	INT_8U data[15] = {'0'};
		
	while(1)
	{
		if(xQueueReceive(mqControl,cmdPacket,portMAX_DELAY))
		{
			while(ind < 30)
			{
				ind++;
				if(cmdPacket[ind]=='$')
				{
					ptrDol_Sign = &cmdPacket[ind];
				}
				if(cmdPacket[ind]=='#')
				{
					ptrHash_Sign = &cmdPacket[ind];
					ind = 0;
					break;
				}
				
			}
			
			if(ptrDol_Sign != NULL && ptrHash_Sign != NULL)
			{
				DataSize = ptrHash_Sign - ptrDol_Sign;
				
				for(ind = 0 ; ind < 15 ; ind++)
				 {
					data[ind]=NULL;
				 }
				 for (ind = 0 ; ind <=DataSize ; ind++)
				 {
					 data[ind] = ptrDol_Sign[ind];
				 }
				 if(strcmp(data,"$SC,ON#")==0)
				 {
					 SELF_CONTROL=1;
					// MQTT_publish("SGH_SC",(INT_8U*)"ON",2,0);
					 vTaskDelay(500);
				 }else if(strcmp(data,"$SC,OFF#")==0)
				 {
					 SELF_CONTROL=0;
					 //MQTT_publish("SGH_SC",(INT_8U*)"OFF",3,0);
					 vTaskDelay(500);
				 }
				  if (SELF_CONTROL==0)
				  {
					if(strcmp(data,"$FAN,ON#")==0)
					{
						Fan_On();
						//MQTT_publish("SGH_FAN",(INT_8U*)"ON",2,0);
						vTaskDelay(500);
					 }else if(strcmp(data,"$FAN,OFF#")==0)
					 {
						Fan_Off();
						//MQTT_publish("SGH_FAN",(INT_8U*)"OFF",3,0);
						vTaskDelay(500);
					 }else if(strcmp(data,"$WP,ON#")==0)
					 {
						 Water_Pump_ON();
						//MQTT_publish("SGH_PUMP",(INT_8U*)"ON",2,0);
						vTaskDelay(500);
					 }else if(strcmp(data,"$WP,OFF#")==0)
					 {
						 Water_Pump_OFF();
						 //MQTT_publish("SGH_PUMP",(INT_8U*)"OFF",3,0);
						 vTaskDelay(500);
						 
					 }else if(strcmp(data,"$LIGHT,100#")==0)
					 {
						 Dim_LED_Stop();
						 //MQTT_publish("SGH_LIGHT",(INT_8U*)"100%",4,0);
						 vTaskDelay(500);
					 }else if(strcmp(data,"$LIGHT,75#")==0)
					 {
						 Dim_LED_Brightness(25);
						 //MQTT_publish("SGH_LIGHT",(INT_8U*)"75%",3,0);
						 vTaskDelay(500);
					 }else if(strcmp(data,"$LIGHT,50#")==0)
					 {
						 Dim_LED_Brightness(50);
						 //QTT_publish("SGH_LIGHT",(INT_8U*)"50%",3,0);
						 vTaskDelay(500);
					 }else if(strcmp(data,"$LIGHT,25#")==0)
					 {
						 Dim_LED_Brightness(75);
						 //MQTT_publish("SGH_LIGHT",(INT_8U*)"25%",3,0);
						 vTaskDelay(500);
					 }else if(strcmp(data,"$LIGHT,0#")==0)
					 {
						 Dim_LED_Brightness(100);
						 //MQTT_publish("SGH_LIGHT",(INT_8U*)"OFF",3,0);
						 vTaskDelay(500);
					 }
				 }
					 ptrDol_Sign = NULL;
					 ptrHash_Sign = NULL;	
			}
		}
	}	
}