/*
 * LDR.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef LDR_H_
#define LDR_H_

#include "adc.h"
#include "Project_Config.h"

void LDR_Init(void);
void LDR_Val (INT_16U* u16LDR_Value);

#endif /* LDR_H_ */