/*
 * T_Monitor.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "T_Monitor.h"

void T_Monitor(void* pvData)
{
		/*	arrays to convert sensors readings to strings
			to be displayed published  	*/
	INT_8U H_data[5] = {'0'};
	INT_8U T_data[5] = {'0'};
	INT_8U soil_arr[5] = {'0'};
	INT_8U light_arr[5] = {'0'};
	EventBits_t ebValues = 0;
	while(1)
	{
		/*  system_up : is set to check on system 
			and created at T_connect*/
		if (system_up == 1)
		{
			MQTT_Ping();
			ebValues = xEventGroupWaitBits(egMQTT,E_MQTT_PINGREQ,1,0,5000);
			if(ebValues&E_MQTT_PINGREQ)
			{
				/* Ping received */
				vTaskDelay(1000);
				
				/* Read,display & publish ldr value */
				LDR_Val(&light);
				sprintf(light_arr,"%d",light);
				MQTT_publish("L_Monitor",(INT_8U*)light_arr,strlen(light_arr),0);		
				LCD_DispStrXY(2,13,(INT_8U*)light_arr);
				vTaskDelay(700);
				/* Read,display & publish soil moisture value */
				Soil_Moisture_Read(&Soil_data);
				sprintf(soil_arr,"%d",Soil_data);
				MQTT_publish("SM_Monitor",(INT_8U*)soil_arr,strlen(soil_arr),0);
				LCD_DispStrXY(1,14,(INT_8U*)soil_arr);
				vTaskDelay(1000);
	
				if ((I_H+D_H+I_Temp+D_Temp) != CheckSum)
				{
					LCD_DispStrXY(1,0,(INT_8U*)"Error");
				}
				else
				{
					/* display & publish humidity value */
					sprintf(H_data,"%d",I_H);
					MQTT_publish("H_Monitor",(INT_8U*)H_data,strlen(H_data),0);
					LCD_DispStrXY(2,5,(INT_8U*)H_data);
					vTaskDelay(700);
					/* display & publish temperature value */
					sprintf(T_data,"%d",I_Temp);
					LCD_DispStrXY(1,6,(INT_8U*)T_data);
					LCD_DispChar(0xDF);
					LCD_DispStr((INT_8U*)"C");
					MQTT_publish("T_Monitor",(INT_8U*)T_data,strlen(T_data),0);
				}	
				}else
				{
					system_up = 0;
					xSemaphoreGive(bsConnect);
				}
			}
		vTaskDelay(8000);	
	}
}