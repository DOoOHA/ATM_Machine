/*
 * EEPROM.h
 *
 * Created: 9/17/2023 6:33:55 PM
 *  Author: DOoOHA
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

void EEPROM_vWrite(unsigned short address, unsigned char data);
unsigned char EEPROM_8uRead(unsigned short address);


#endif /* EEPROM_H_ */