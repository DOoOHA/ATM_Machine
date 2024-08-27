/*
 * KeyPad.c
 *
 * Created: 11/27/2023 12:12:04 AM
 *  Author: DOoOHA
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "KeyPad.h"
#include "../MCAL/DIO.h"

void KeyPad_vInit(void)
{
	//DIO_vSET_LowNibble_DIRECTION(ro, 1);
	//DIO_vSET_HighNibble_DIRECTION(col, 0);
	DIO_vSET_PORT_DIRECTION(ro, 0x0f);
	DIO_vWRITE_HighNibble(col, 0x0f);
}

char Read_KeyPad(void)
{
	//char key_Pad[4][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}}; // --> Hardware
	char key_Pad[4][4] = {{'7', '8', '9', '/'}, {'4', '5', '6', '*'}, {'1', '2', '3', '-'}, {'c', '0', '=', '+'}}; // --> Proteus
	char level = 1, data = NotPressed;
	for (unsigned char i = 0; i < 4; i++)
	{
		DIO_vWRITE_LowNibble(ro, 0x0f);
		DIO_vWRITE_PIN(ro, i, 0);
		for (unsigned char j = 0; j < 4; j++)
		{
			level = DIO_u8READ_PIN(col, j + 4);
			if (level == 0)
			{
				data = key_Pad[i][j];
				while(DIO_u8READ_PIN(col, j + 4) == 0);
				break;
			}
		}
		if (level == 0)
		{
			break;
		}
	}
	return data;
}

