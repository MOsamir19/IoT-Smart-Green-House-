/*
 * Board.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef BOARD_H_
#define BOARD_H_

#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"

#define  BUZ_PORT   PORTE
#define  BUZ_DDR    DDRE
#define  BUZ_PIN    PE7

#define  LED_PORT   PORTB
#define  LED_DDR    DDRB
#define  LED_PIN    PB4

#define  BUTTON_PORT   PORTD
#define  BUTTON_DDR    DDRD
#define  BUTTON_PINR   PIND

typedef enum{
	BUTTON0, BUTTON1
	}BUTTON;
	
typedef enum{
	IN_STATE_NONE, IN_STATE_PULLUP
	}IN_STATE;

#define  LEDS_PORT   PORTA
#define  LEDS_DDR    DDRA

void Led_Init(void);
void Led_On(void);
void Led_Off(void);
void Led_Toggle(void);

void Buz_Init(void);
void Buz_On(void);
void Buz_Off(void);
void Buz_Toggle(void);

void Leds_Init(INT_8U u8Leds);void Leds_On(INT_8U u8Leds);void Leds_Off(INT_8U u8Leds);void Leds_Toggle(INT_8U u8Leds);


void BTN_Init(BUTTON btn, IN_STATE btnInState);
Bool BTN_isPressed (BUTTON btn);

#endif /* BOARD_H_ */