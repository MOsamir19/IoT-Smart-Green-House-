/*
 * App.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "App.h"

/* OS Services  */

xSemaphoreHandle     bsConnect;
xQueueHandle         mqControl;
xQueueHandle         DHTreadings;
EventGroupHandle_t   egMQTT;
EventBits_t          ebValuesMQTT;
INT_8U	I_H = 0;
INT_8U	D_H = 0;
INT_8U	I_Temp = 0;
INT_8U	D_Temp = 0;
INT_8U	CheckSum = 0;

int main(void)
{
	/* Replace with your application code */

	System_Init();
	/* create OS Services */
	vSemaphoreCreateBinary(bsConnect,1);
	mqControl = xQueueCreate(2,30);  // length = 2  * (30 bytes)
	//DHTreadings = xQueueCreate(10,1);
	egMQTT = xEventGroupCreate();
	
	/* create tasks */
	
	xTaskCreate(T_Self_Control,"T_Self_Control",150,NULL,1,NULL);
	xTaskCreate(T_Monitor,"T_Monitor",150,NULL,2,NULL);
	xTaskCreate(T_Control,"T_Control",150,NULL,3,NULL);
	xTaskCreate(T_Connect,"T_Connect",200,NULL,4,NULL);
	xTaskCreate(T_RespHandle,"T_RespHandle",100,NULL,5,NULL);
	
	
	/* Start OS */
	
	vTaskStartScheduler();
	
	
	while(1)
	{
		
	}
}
		/* DHT11 function to be called 
				during interrupt   */
void DHT_Monitor(void)
{
	if(system_up == 1)
	{
		Start_Signal();
		Response_Signal();
		I_H				=	Receive_data();
		D_H				=	Receive_data();
		I_Temp			=	Receive_data();
		D_Temp			=	Receive_data();
		CheckSum		=	Receive_data();
	}	
}
	/* Initialize needed prephirals*/
void System_Init(void)
{
	Timer0_Init(MODE_NORMAL);
	LDR_Init();
	MQTT_Init();
	ADC_INIT();
	Fan_Init();
	Soil_Moisture_Init();
	Water_Pump_Init();
	LCD_Init();
	Dim_LED_Init();
	Wifi_Init(Station);
	Timer0_SetNotification(DHT_Monitor,10000);
	sei();
}
