/*
 * SOIL_MOISTURE.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef SOIL_MOISTURE_H_
#define SOIL_MOISTURE_H_

#include	"avr/io.h"
#include	"bit_handle.h"
#include	"data_types.h"
#include	"ADC.h"
#include	"Project_Config.h"

		/*Sensor*/
void Soil_Moisture_Init(void);
void Soil_Moisture_Read(INT_16U* COPY_u16Data);

	/*Water Pump*/
void Water_Pump_Init(void);
void Water_Pump_ON(void);
void Water_Pump_OFF(void);


#endif /* SOIL_MOISTURE_H_ */