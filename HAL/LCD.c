/*
 * LCD.c
 *
 * Created: 9/26/2023 4:02:54 PM
 *  Author: LENOVO
 */ 

#define F_CPU 8000000UL

#include "DIO.h"
#include "LCD.h"
#include <util/delay.h>

void LCD_Send_vChar(char data)
{
	#if LCD_MODE == 8
	DIO_vWRITE_PORT(LCD_CONNECT, data);
	DIO_vWRITE_PIN(LCD_CONTROL, RS, 1);
	Enable();
	#elif LCD_MODE == 4
		#if NIBBLE == 0
		DIO_vWRITE_LowNibble(LCD_CONNECT, data>>4);
		DIO_vWRITE_PIN(LCD_CONTROL, RS, 1);
		Enable();
		DIO_vWRITE_LowNibble(LCD_CONNECT, data);
		Enable();
		#elif NIBBLE == 1
		DIO_vWRITE_HighNibble(LCD_CONNECT, data>>4);
		DIO_vWRITE_PIN(LCD_CONTROL, RS, 1);
		Enable();
		DIO_vWRITE_HighNibble(LCD_CONNECT, data);
		Enable();
		#endif
	#endif
	_delay_ms(1);
}

static void Enable()
{
	DIO_vWRITE_PIN(LCD_CONTROL, E, 1);
	_delay_ms(2);
	DIO_vWRITE_PIN(LCD_CONTROL, E, 0);
	_delay_ms(2);
}

void LCD_Send_vCmd(char cmd)
{
	#if LCD_MODE == 8
	
	if (cmd == CLEAR_SCREEN || cmd == RETURN_HOME)
	{
		DIO_vWRITE_PORT(LCD_CONNECT, cmd);
		DIO_vWRITE_PIN(LCD_CONTROL, RS, 0);
		Enable();
		_delay_ms(10);
	}
	else
	{
		DIO_vWRITE_PORT(LCD_CONNECT, cmd);
		DIO_vWRITE_PIN(LCD_CONTROL, RS, 0);
		Enable();
		_delay_ms(1);
	}
	
	#elif LCD_MODE == 4
		#if NIBBLE == 0
		if (cmd == CLEAR_SCREEN || cmd == RETURN_HOME)
		{
			DIO_vWRITE_LowNibble(LCD_CONNECT, cmd>>4);
			DIO_vWRITE_PIN(LCD_CONTROL, RS, 0);
			Enable();
			_delay_ms(10);
			DIO_vWRITE_LowNibble(LCD_CONNECT, cmd);
			Enable();
			_delay_ms(10);
		}
		else
		{
			DIO_vWRITE_LowNibble(LCD_CONNECT, cmd>>4);
			DIO_vWRITE_PIN(LCD_CONTROL, RS, 0);
			Enable();
			_delay_ms(1);
			DIO_vWRITE_LowNibble(LCD_CONNECT, cmd);
			Enable();
			_delay_ms(1);
		}
	
		#elif NIBBLE == 1
		if (cmd == CLEAR_SCREEN || cmd == RETURN_HOME)
		{
			DIO_vWRITE_HighNibble(LCD_CONNECT, cmd>>4);
			DIO_vWRITE_PIN(LCD_CONTROL, RS, 0);
			Enable();
			_delay_ms(10);
			DIO_vWRITE_HighNibble(LCD_CONNECT, cmd);
			Enable();
			_delay_ms(10);
		}
		else
		{
			DIO_vWRITE_HighNibble(LCD_CONNECT, cmd>>4);
			DIO_vWRITE_PIN(LCD_CONTROL, RS, 0);
			Enable();
			_delay_ms(1);
			DIO_vWRITE_HighNibble(LCD_CONNECT, cmd);
			Enable();
			_delay_ms(1);
		}
		
		#endif
	
	#endif
}


void LCD_vInit()
{
	_delay_ms(30);
	#if LCD_MODE == 8
	
	DIO_vSET_PORT_DIRECTION(LCD_CONNECT, 0xff);
	DIO_vSET_PIN_DIRECTION(LCD_CONTROL, E, 1);
	DIO_vSET_PIN_DIRECTION(LCD_CONTROL, RS, 1);
	LCD_Send_vCmd(EIGHT_BIT_MODE);
	LCD_Send_vCmd(DisplayON_CursorOFF);
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_Send_vCmd(Entry_MODE);
	
	#elif LCD_MODE == 4
	
		#if NIBBLE == 0
		DIO_vSET_LowNibble_DIRECTION(LCD_CONNECT, 1);
		#elif NIBBLE == 1
		DIO_vSET_HighNibble_DIRECTION(LCD_CONNECT, 1);
		#endif
	DIO_vSET_PIN_DIRECTION(LCD_CONTROL, E, 1);
	DIO_vSET_PIN_DIRECTION(LCD_CONTROL, RS, 1);
	LCD_Send_vCmd(RETURN_HOME);
	LCD_Send_vCmd(FOUR_BIT_MODE);
	LCD_Send_vCmd(DisplayON_CursorOFF);
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_Send_vCmd(Entry_MODE);
	
	#endif
}

void LCD_Send_vString(char *ptr)
{
	while(*ptr != '\0')
	{
		LCD_Send_vChar(*ptr);
		ptr++;
	}
}

void LCD_vMove_Cursor(unsigned char row, unsigned char column)
{
	unsigned char cmd;
	if (row < 1 || row > 2 || column < 1 || column > 16)
	{
		cmd = 0x80;
	}
	else if(row == 1)
	{
		cmd = 0x80 + column - 1;
	}
	else if (row == 2)
	{
		cmd = 0xc0 + column - 1;
	}
	
	LCD_Send_vCmd(cmd);
}
