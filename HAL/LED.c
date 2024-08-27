/*
 * LED.c
 *
 * Created: 9/4/2023 8:26:47 AM
 *  Author: DOoOHA
 */ 

#include "../MCAL/DIO.h"

void LED_vINIT(unsigned char port, unsigned char pin)
{
	DIO_vSET_PIN_DIRECTION(port, pin, 1);
}

void LED_vTurnON(unsigned char port, unsigned char pin)
{
	DIO_vWRITE_PIN(port, pin, 1);
}

void LED_vTurnOFF(unsigned char port, unsigned char pin)
{
	DIO_vWRITE_PIN(port, pin, 0);
}

void LED_vTOGGLE(unsigned char port, unsigned char pin)
{
	DIO_vTOG_PIN(port, pin);
}

unsigned char LED_READ_STATUS(unsigned char port, unsigned char pin)
{
	return DIO_u8READ_PIN(port, pin);
}




