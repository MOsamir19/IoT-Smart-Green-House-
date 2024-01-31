/*
 * LCD4bit.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef LCD4BIT_H_
#define LCD4BIT_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "bit_handle.h"
#include "data_types.h"
#include "util/delay.h"
#include <string.h>

#define LCD_DATA_PORT		PORTC
#define LCD_DATA_DDR		DDRC
#define LCD_DATA_MSK        0xF0

#define LCD_CTRL_PORT		PORTB
#define LCD_CTRL_DDR		DDRB

#define	LCD_RS				PB5
#define	LCD_EN				PB7
#define LCD_RW              PB6

#define LCD_BL_PORT         PORTE
#define LCD_BL_DDR          DDRE
#define LCD_BL_PIN          PE4

#define BACK_TO_HOME        0x02
#define CMD_4BIT_MODE       0x28
#define CMD_CLEAR			0x01
#define CMD_ENTRY_MODE		0x06
#define CMD_DISP_ON			0x0C
#define CMD_CFG				0x38

/* x (1-2 line), y (1-16) cols */
void LCD_Init(void);
void LCD_Clear(void);
void LCD_DispChar(INT_8U u8Char);
void LCD_DispStr(INT_8U* pu8Str);
void LCD_DispCharXY(INT_8U x, INT_8U y, INT_8U u8Char);
void LCD_DispStrXY(INT_8U x, INT_8U y, INT_8U* pu8Str);
unsigned char* float_to_ascii(float num);



#endif /* LCD4BIT_H_ */