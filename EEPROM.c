/*
 * EEPROM.c
 *
 * Created: 9/17/2023 6:33:42 PM
 *  Author: DOoOHA
 */ 
#include <avr/io.h>
#include "bitwise_macros.h"


void EEPROM_vWrite(unsigned short address, unsigned char data)
{
	EEDR = data;
	EEARL = (char)address;
	EEARH = (char)(address>>8);
	SET_BIT(EECR, EEMWE);
	SET_BIT(EECR, EEWE);
	while(READ_BIT(EECR, EEWE) == 1);
}



unsigned char EEPROM_8uRead(unsigned short address)
{
	EEARL = (char)address;
	EEARH = (char)(address>>8);
	SET_BIT(EECR, EERE);
	return EEDR;
}
