/*
 * LCD4bit.c
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#include "LCD4bit.h"
static void LCD_SendCmd(INT_8U u8Cmd);
static void LCD_SendData(INT_8U u8Data);
static void LCD_GotoXY(INT_8U x, INT_8U y);

static void LCD_SendCmd(INT_8U u8Cmd){
	/* RS -> 0 */
	CLEARBIT(LCD_CTRL_PORT,LCD_RS);
	/* upload MSB of  u8Cmd*/
	
	CLEARBITS(LCD_DATA_PORT,LCD_DATA_MSK);
	LCD_DATA_PORT|=(u8Cmd&0xF0);
	
	/* high and low for EN */
	
	SETBIT(LCD_CTRL_PORT,LCD_EN);
	_delay_ms(1);
	CLEARBIT(LCD_CTRL_PORT,LCD_EN);
	_delay_ms(1);
	
	/* upload the LSB of u8cmd */
	CLEARBITS(LCD_DATA_PORT,LCD_DATA_MSK);
	LCD_DATA_PORT|=((u8Cmd&0x0F)<<4);     //shifting the LSB to the  MSB
		
	/* high and low for EN */
		
	SETBIT(LCD_CTRL_PORT,LCD_EN);
	_delay_ms(1);
	CLEARBIT(LCD_CTRL_PORT,LCD_EN);
	_delay_ms(1);
	
	/* wait 40 us */	
	_delay_us(40);
}
static void LCD_SendData(INT_8U u8Data){
		/* RS -> 1 */
		SETBIT(LCD_CTRL_PORT,LCD_RS);
		/* upload MSB of  u8Cmd*/
		
		CLEARBITS(LCD_DATA_PORT,LCD_DATA_MSK);
		LCD_DATA_PORT|=(u8Data&0xF0);
		
		/* high and low for EN */
		
		SETBIT(LCD_CTRL_PORT,LCD_EN);
		_delay_ms(1);
		CLEARBIT(LCD_CTRL_PORT,LCD_EN);
		_delay_ms(1);
		
		/* upload the LSB of u8cmd */
		CLEARBITS(LCD_DATA_PORT,LCD_DATA_MSK);
		
		LCD_DATA_PORT|=((u8Data&0x0F)<<4);    //shifting the LSB to the  MSB
		
		/* high and low for EN */
		
		SETBIT(LCD_CTRL_PORT,LCD_EN);
		_delay_ms(1);
		CLEARBIT(LCD_CTRL_PORT,LCD_EN);
		_delay_ms(1);
		
		/* wait 40 us */
		_delay_us(40);
}
/* 
	Line 1: 0x00
	Line 2: 0x40
*/
static void LCD_GotoXY(INT_8U x, INT_8U y){
	/* get address of DDRAM using x,y */
	if(x == 1){
		LCD_SendCmd((0x80|0x00) + y-1); /* Eqn */
	}
	else{
		LCD_SendCmd((0x80|0x40) + y-1); /* Eqn */
	}
}
void LCD_Init(void){
	/* Directions -> OUT */
	SETBITS(LCD_DATA_DDR,LCD_DATA_MSK);
	
	SETBIT(LCD_CTRL_DDR,LCD_EN);
	SETBIT(LCD_CTRL_DDR,LCD_RS);
	SETBIT(LCD_CTRL_DDR,LCD_RW);
	CLEARBIT(LCD_CTRL_PORT,LCD_RW);
	/* Back Light */	SETBIT(LCD_BL_DDR,LCD_BL_PIN);	SETBIT(LCD_BL_PORT,LCD_BL_PIN);
	
	/* delay -> 20 ms (power on lcd) */
	    _delay_ms(20);
	/* send CMDS */
		LCD_SendCmd(BACK_TO_HOME);
		LCD_SendCmd(CMD_4BIT_MODE);
		LCD_SendCmd(CMD_CLEAR);
		LCD_SendCmd(CMD_DISP_ON);	
		LCD_SendCmd(CMD_ENTRY_MODE);
	    _delay_ms(20);
	    
}
void LCD_Clear(void){
	/* CMD_CLEAR */
	LCD_SendCmd(CMD_CLEAR);
	/* delay 5 ms */
	_delay_ms(5);
}
void LCD_DispChar(INT_8U u8Char){
	LCD_SendData(u8Char);
}
void LCD_DispStr(INT_8U* pu8Str){
	for(int i=0;i<strlen((const char*)pu8Str);i++)
	{
		LCD_SendData(pu8Str[i]);
	}
}
void LCD_DispCharXY(INT_8U x, INT_8U y, INT_8U u8Char){
	LCD_GotoXY(x,y);
	LCD_DispChar(u8Char);
}
void LCD_DispStrXY(INT_8U x, INT_8U y, INT_8U* pu8Str){
	LCD_GotoXY(x,y);
	LCD_DispStr(pu8Str);
}


uint8_t* float_to_ascii(float num)
{
	static unsigned char str[10]={0};
	char strtemp[10]={0};
	int Intpart=(int)num;
	float Fltpart=num-Intpart;
	int DecimalCounter =0;
	float temp=Fltpart;
	
	while (temp<1.0 && temp!=0.0)
	{
		temp*=10;
		DecimalCounter++;
		
	}
	temp*=10;
	if (DecimalCounter!=0)
	{
		memset(strtemp,'0',DecimalCounter-1);
	}
	sprintf((char*)str,"%d.%s%d",Intpart,strtemp,(int)temp);
	return str;
}
