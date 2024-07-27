/*
 * DIO.c
 *
 * Created: 9/2/2023 10:40:34 PM
 *  Author: DOoOHA
 */ 

#include "bitwise_macros.h"
#include <avr/io.h>

void DIO_vSET_PIN_DIRECTION(unsigned char port, unsigned char pin, unsigned char direction)
{
	switch(port)
	{
		case 'A':
		case 'a':
		if(direction == 1)
		{
			SET_BIT(DDRA,pin);
		}
		else
		{
			CLR_BIT(DDRA,pin);
		}
		break;
		case 'B':
		case 'b':
		if(direction == 1)
		{
			SET_BIT(DDRB,pin);
		}
		else
		{
			CLR_BIT(DDRB,pin);
		}
		break;
		case 'C':
		case 'c':
		if(direction == 1)
		{
			SET_BIT(DDRC,pin);
		}
		else
		{
			CLR_BIT(DDRC,pin);
		}
		break;
		case 'D':
		case 'd':
		if(direction == 1)
		{
			SET_BIT(DDRD,pin);
		}
		else
		{
			CLR_BIT(DDRD,pin);
		}
		break;
		default:
		break;
	}
}


void DIO_vConnect_PullUp(unsigned char port, unsigned char pin, unsigned char connect)
{
	DIO_vWRITE_PIN(port, pin, connect);
}



void DIO_vWRITE_PIN(unsigned char port, unsigned char pin, unsigned char output)
{
	switch(port)
	{
		case 'A':
		case 'a':
		if (output == 1)
		{
			SET_BIT(PORTA,pin);
		}
		else
		{
			CLR_BIT(PORTA,pin);
		}
		break;
		case 'B':
		case 'b':
		if (output == 1)
		{
			SET_BIT(PORTB,pin);
		}
		else
		{
			CLR_BIT(PORTB,pin);
		}
		break;
		case 'C':
		case 'c':
		if (output == 1)
		{
			SET_BIT(PORTC,pin);
		}
		else
		{
			CLR_BIT(PORTC,pin);
		}
		break;
		case 'D':
		case 'd':
		if (output == 1)
		{
			SET_BIT(PORTD,pin);
		}
		else
		{
			CLR_BIT(PORTD,pin);
		}
		break;
		default:
		break;
	}
}


unsigned char DIO_u8READ_PIN(unsigned char port, unsigned char pin)
{
	unsigned char data = 0;
	switch(port)
	{
		case 'A':
		case 'a':
		data = READ_BIT(PINA,pin);
		break;
		case 'B':
		case 'b':
		data = READ_BIT(PINB,pin);
		break;
		case 'C':
		case 'c':
		data = READ_BIT(PINC,pin);
		break;
		case 'D':
		case 'd':
		data = READ_BIT(PIND,pin);
		break;
		default:
		break;
	}
	return data;
}

void DIO_vTOG_PIN(unsigned char port, unsigned char pin)
{
	switch(port)
	{
		case 'A':
		case 'a':
		TOG_BIT(PORTA,pin);
		break;
		case 'B':
		case 'b':
		TOG_BIT(PORTB,pin);
		break;
		case 'C':
		case 'c':
		TOG_BIT(PORTC,pin);
		break;
		case 'D':
		case 'd':
		TOG_BIT(PORTD,pin);
		break;
		default:
		break;
	}
}


void DIO_vSET_PORT_DIRECTION(unsigned char port,unsigned char direction)
{
	switch(port)
	{
		case 'A':
		case 'a':
		DDRA = direction;
		break;
		case 'B':
		case 'b':
		DDRB = direction;
		break;
		case 'C':
		case 'c':
		DDRC = direction;
		break;
		case 'D':
		case 'd':
		DDRD = direction;
		break;
		default:
		break;
	}
}


void DIO_vWRITE_PORT(unsigned char port,unsigned char output)
{
	switch(port)
	{
		case 'A':
		case 'a':
		PORTA = output;
		break;
		case 'B':
		case 'b':
		PORTB = output;
		break;
		case 'C':
		case 'c':
		PORTC = output;
		break;
		case 'D':
		case 'd':
		PORTD = output;
		break;
		default:
		break;
	}
}


unsigned char DIO_u8READ_PORT(unsigned char port)
{
	unsigned char data = 0;
	switch(port)
	{
		case 'A':
		case 'a':
		data = PINA;
		break;
		case 'B':
		case 'b':
		data = PINB;
		break;
		case 'C':
		case 'c':
		data = PINC;
		break;
		case 'D':
		case 'd':
		data = PIND;
		break;
		default:
		break;
	}
	return data;
}


void DIO_vTOG_PORT(unsigned char port)
{
	switch(port)
	{
		case 'A':
		case 'a':
		PORTA = ~PORTA;
		break;
		case 'B':
		case 'b':
		PORTB = ~PORTB;
		break;
		case 'C':
		case 'c':
		PORTC = ~PORTC;
		break;
		case 'D':
		case 'd':
		PORTD = ~PORTD;
		break;
		default:
		break;
	}
}


void DIO_vSET_LowNibble_DIRECTION(unsigned char port, unsigned char direction)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		DIO_vSET_PIN_DIRECTION(port, i, direction);
	}
}


void DIO_vSET_HighNibble_DIRECTION(unsigned char port, unsigned char direction)
{
	for (unsigned char i = 4; i < 8; i++)
	{
		DIO_vSET_PIN_DIRECTION(port, i, direction);
	}
}


void DIO_vWRITE_LowNibble(unsigned char port, unsigned char output)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		DIO_vWRITE_PIN(port, i, READ_BIT(output, i));
	}
}


void DIO_vWRITE_HighNibble(unsigned char port, unsigned char output)
{
	for (unsigned char i = 4, j = 0; i < 8; i++, j++)
	{
		DIO_vWRITE_PIN(port, i, READ_BIT(output, j));
	}
}
