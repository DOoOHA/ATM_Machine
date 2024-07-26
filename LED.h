/*
 * LED.h
 *
 * Created: 9/4/2023 8:27:02 AM
 *  Author: DOoOHA
 */ 


#ifndef LED_H_
#define LED_H_

void LED_vINIT(unsigned char port, unsigned char pin);
void LED_vTurnON(unsigned char port, unsigned char pin);
void LED_vTurnOFF(unsigned char port, unsigned char pin);
void LED_vTOGGLE(unsigned char port, unsigned char pin);
unsigned char LED_READ_STATUS(unsigned char port, unsigned char pin);

#endif /* LED_H_ */