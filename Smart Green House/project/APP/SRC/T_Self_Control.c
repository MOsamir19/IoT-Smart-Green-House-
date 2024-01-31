/*
 * T_Self_Control.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "T_Self_Control.h"

void T_Self_Control(void* pvData)
{
	INT_8U X =0 ,y =0  ;
	INT_8U z1=0,z2=0,z3=0,z4=0,z5=0 ;
	
	while (1)
	{
		if (SELF_CONTROL == 1)
		{
			if (Soil_data>=0 && Soil_data<=40 && X==0)
			{
				X=1 ;
				Water_Pump_ON();
				if(system_up == 1)
				{
					//MQTT_publish("SGH_PUMP","ON",2,0);
					vTaskDelay(500);
				}		
			}
			else if (Soil_data>40 && Soil_data<=100 && X==1)
			{
				X=0;
				Water_Pump_OFF();
				if(system_up == 1)
				{
					//MQTT_publish("SGH_PUMP","OFF",3,0);
					vTaskDelay(500);
				}
			}
			else{}
			if (I_Temp>35 && I_Temp<60 && y==0)
			{
				Fan_On();
				if(system_up == 1)
				{
					//MQTT_publish("SGH_FAN","ON",2,0);
					vTaskDelay(500);
				}
				y=1 ;
			}
			else if (I_Temp>0 && I_Temp<35 && y==1)
			{
				Fan_Off();
				if (system_up == 1)
				{
					//MQTT_publish("SGH_FAN","OFF",3,0);
					vTaskDelay(500);
				}
				y=0;
			}
			else{}
				if (light>80 && light<=100 &&  z1 == 0 )
				{
					//Dim_LED_Stop();
					if (system_up == 1)
					{
						Dim_LED_Brightness(100);
						//MQTT_publish("SGH_LIGHT","OFF",3,0);
						vTaskDelay(500);
					}
					z1=1;
					z2=0;
					z3=0;
					z4=0;
					z5=0;
				}
				else if (light>=60 && light<=80 && z2 == 0)
				{
					Dim_LED_Brightness(75);
					if (system_up == 1)
					{
						//MQTT_publish("SGH_LIGHT","25%",3,0);
						vTaskDelay(500);
					}
					z1=0;
					z2=1;
					z3=0;
					z4=0;
					z5=0;	
				}
				else if (light>=40 && light<60 && z3 == 0 )
				{
					Dim_LED_Brightness(50);
					if (system_up == 1)
					{
						//MQTT_publish("SGH_LIGHT","50%",3,0);
						vTaskDelay(500);
					}
					z1=0;
					z2=0;
					z3=1;
					z4=0;
					z5=0;	
				}
				else if (light>=20 && light<40 && z4 == 0 )
				{
					Dim_LED_Brightness(25);
					
					if (system_up == 1)
					{		
						//MQTT_publish("SGH_LIGHT","75%",3,0);
						vTaskDelay(500);
					}
					z1=0;
					z2=0;
					z3=0;
					z4=1;
					z5=0;	
				}
				else if (light>=0 && light<20 && z5==0 )
				{
					Dim_LED_Stop();
					
					if (system_up == 1)
					{
						//MQTT_publish("SGH_LIGHT","100%",4,0);
						vTaskDelay(500);
					}
					z1=0;
					z2=0;
					z3=0;
					z4=0;
					z5=1;
				}
				else{}	
		}
		vTaskDelay(5000);
	}	
}