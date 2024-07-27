/*
 * DIO.h
 *
 * Created: 9/2/2023 10:40:48 PM
 *  Author: DOoOHA
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "bitwise_macros.h"

void DIO_vSET_PIN_DIRECTION(unsigned char port, unsigned char pin, unsigned char direction);
void DIO_vSET_LowNibble_DIRECTION(unsigned char port, unsigned char direction);
void DIO_vSET_HighNibble_DIRECTION(unsigned char port, unsigned char direction);
void DIO_vConnect_PullUp(unsigned char port, unsigned char pin, unsigned char connect);
void DIO_vWRITE_PIN(unsigned char port, unsigned char pin, unsigned char output);
void DIO_vWRITE_LowNibble(unsigned char port, unsigned char output);
void DIO_vWRITE_HighNibble(unsigned char port, unsigned char output);
unsigned char DIO_u8READ_PIN(unsigned char port, unsigned char pin);
void DIO_vTOG_PIN(unsigned char port, unsigned char pin);
void DIO_vSET_PORT_DIRECTION(unsigned char port,unsigned char direction);
void DIO_vWRITE_PORT(unsigned char port,unsigned char output);
unsigned char DIO_u8READ_PORT(unsigned char port);
void DIO_vTOG_PORT(unsigned char port);

#endif /* DIO_H_ */