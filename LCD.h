/*
 * LCD.h
 *
 * Created: 9/26/2023 4:03:16 PM
 *  Author: DOoOHA
 */ 


#ifndef LCD_H_
#define LCD_H_

///////////////////////
#include "Lcd_Conf.h"
//////////////////////

#if LCD_MODE == 4
#define NIBBLE 1 //>>>>>>>>>> which nibble HIGH(1)/LOW(0) for selected port
#endif
#define LCD_CONNECT 'D'
#define LCD_CONTROL 'c'
#define E 0 //which pin in LCD_CONTROL port
#define RS 1 //which pin in LCD_CONTROL port

#define DisplayON_CursorON 0x0e
#define DisplayOFF_CursorOFF 0x08
#define DisplayOFF_CursorON 0x0a
#define DisplayON_CursorOFF 0x0c
#define SHIFT_Cursor_LEFT 0x04
#define ROTATE_RIGHT 0x1c
#define ROTATE_LEFT 0x18
#define EIGHT_BIT_MODE 0x38
#define FOUR_BIT_MODE 0x28
#define CLEAR_SCREEN 0x01
#define RETURN_HOME 0x02
#define Entry_MODE 0x06

void LCD_vMove_Cursor(unsigned char row, unsigned char column);
void LCD_Send_vString(char *ptr);
void LCD_vInit(void);
void LCD_Send_vCmd(char cmd);
static void Enable(void);
void LCD_Send_vChar(char data);


#endif /* LCD_H_ */