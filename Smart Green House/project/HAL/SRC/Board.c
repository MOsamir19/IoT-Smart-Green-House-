/*
 * Board.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "Board.h"

void Led_Init(void)
{   /* out */
	SETBIT(LED_DDR,LED_PIN);
	/* led off */
	Led_Off();
}
void Led_On(void)
{
	/* high */
	SETBIT(LED_PORT, LED_PIN);
}
void Led_Off(void)
{
    /* low */
    CLEARBIT(LED_PORT, LED_PIN);	
}
void Led_Toggle(void)
{
	/* toggle */
	TOGGLEBIT(LED_PORT, LED_PIN);
}

void Buz_Init(void)
{
	 /* out */
	 SETBIT(BUZ_DDR,BUZ_PIN);
	 /* buzzer off */
	 Buz_Off();
}
void Buz_On(void)
{
	SETBIT(BUZ_PORT,BUZ_PIN);
}
void Buz_Off(void)
{
	CLEARBIT(BUZ_PORT,BUZ_PIN);
}
void Buz_Toggle(void)
{
	TOGGLEBIT(BUZ_PORT,BUZ_PIN);
}

void Leds_Init(INT_8U u8Leds){	/* out */
	SETBITS(LEDS_DDR,u8Leds);
	/* leds off */
	Leds_Off(u8Leds);}void Leds_On(INT_8U u8Leds){	SETBITS(LEDS_PORT,u8Leds);}void Leds_Off(INT_8U u8Leds){	CLEARBITS(LEDS_PORT,u8Leds);}void Leds_Toggle(INT_8U u8Leds)
{
	TOGGLEBITS(LEDS_PORT,u8Leds);
}


void BTN_Init(BUTTON btn, IN_STATE btnInState)
{
	/* input */
	CLEARBIT(BUTTON_DDR,btn);
	/* activate pull up */
	switch (btnInState)
	{
		case IN_STATE_NONE:
		     CLEARBIT(BUTTON_PORT, btn);
		break;
		case IN_STATE_PULLUP:
		     SETBIT(BUTTON_PORT, btn);
		break;
	}
	
}
Bool BTN_isPressed (BUTTON btn)
{
	return (!readbit(BUTTON_PINR,btn));
}
