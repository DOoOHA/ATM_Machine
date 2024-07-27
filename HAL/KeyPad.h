/*
 * KeyPad.h
 *
 * Created: 11/27/2023 12:12:15 AM
 *  Author: DOoOHA
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

//which port will connect with KeyPad Pins
#define  ro 'b' //output low nibble
#define  col 'b' //input High nibble
#define  NotPressed 0xff

void KeyPad_vInit(void);
char Read_KeyPad(void);



#endif /* KEYPAD_H_ */