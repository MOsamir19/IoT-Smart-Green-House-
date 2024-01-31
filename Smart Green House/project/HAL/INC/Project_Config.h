/*
 * Project_Config.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef PROJECT_CONFIG_H_
#define PROJECT_CONFIG_H_

		/*	Configuration	*/

/* Soil_Moisture_Sensor ADC channel */
#define Soil_Moisture_channel  channel_7

/* Water_Pump Ports & Pin */
#define Water_Pump_DDR			DDRD
#define Water_Pump_PORT			PORTD
#define Water_Pump_PIN_Number	PD0


/*********************************************/

/* DHT11_Sensor Ports & Pin */
#define DHT11_DDR		DDRE
#define DHT11_PORT		PORTE
#define DHT11_PIN		PINE
#define DHT11_Data		PE2

/* Fan Ports & Pin */
#define Fan_DDR			DDRF
#define Fan_PORT		PORTF
#define Fan_PIN_Number  PF3

/*********************************************/

/* LDR ADC channel */
#define LDR_channel		channel_2

#endif 