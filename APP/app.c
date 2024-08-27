/*
 * app.c
 *
 * Created: 6/27/2024 9:29:56 PM
 *  Author: DOoOHA
 */ 

#define EEPROM_STATUS_LOCATION 0x20
#define EEPROM_PASSWORD_LOCATION1 0x21
#define EEPROM_PASSWORD_LOCATION2 0x22
#define EEPROM_PASSWORD_LOCATION3 0x23
#define EEPROM_PASSWORD_LOCATION4 0x24
#define NUMBER_OF_PASSWORD 4
#define MAX_TRIES 3

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../MCAL/bitwise_macros.h"
#include "../MCAL/TIMERS.h"
#include "../HAL/KeyPad.h"
#include "../MCAL/EEPROM.h"
#include "../HAL/LCD.h"
#include "../MCAL/DIO.h"
#include "../HAL/LED.h"
#include "../MCAL/ADC.h"

extern volatile unsigned char temperature;
unsigned int current_balance = 1500;
extern char system_open_flag;
volatile char counter_sec;
unsigned char trial;

void modules_init (void)
{
	KeyPad_vInit();
	ADC_Init();
	LCD_vInit();
	LED_vINIT('c', 2);
	LED_vINIT('c', 3);
	LED_vINIT('c', 4);
	//For Motors
	DIO_vSET_LowNibble_DIRECTION('D', 1);
}



void current_salary() 
{
	ADC_StartConversion();
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("Current Balance");
	LCD_vMove_Cursor(2,4);
	LCD_Send_vChar((current_balance/1000) + '0');
	LCD_Send_vChar((current_balance%1000) / 100 + '0');
	LCD_Send_vChar( ((current_balance%100)/ 10) + '0');
	LCD_Send_vChar((current_balance % 10) + '0');
	ADC_StartConversion();
	_delay_ms(3000);
}

void deposit ()
{
	unsigned char digits[10] = {0};
	unsigned char counter = 0;
	unsigned int sum;
	char DP;
	ADC_StartConversion();
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("Enter Value:");
	LCD_vMove_Cursor(2,1);
	while ((DP =  Read_KeyPad()) != '=')
	{
		ADC_StartConversion();
		if (DP != NotPressed)
		{
			LCD_Send_vChar(DP);
			digits[counter] = (DP - '0');
			counter++;
		}
	}
	ADC_StartConversion();
	
	DIO_vWRITE_PORT('d',0x05);
	LED_vTurnON('c',3);
	_delay_ms(3000);
	DIO_vWRITE_PORT('d',0x00);
	LED_vTurnOFF('c',3);
	
	sum = digits[0];
	for (unsigned char i = 1; i < counter; i++)
	{
		sum = sum*10 + digits[i];
	}
	current_balance += sum ;
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("Current Balance");
	LCD_vMove_Cursor(2,4);
	LCD_Send_vChar((current_balance/1000) + '0');
	LCD_Send_vChar((current_balance%1000) / 100 + '0');
	LCD_Send_vChar( ((current_balance%100)/ 10) + '0');
	LCD_Send_vChar((current_balance % 10) + '0');
	ADC_StartConversion();
	_delay_ms(2000);
}

char check_password (void)
{
	unsigned wrong_pass_flag, password, trial = MAX_TRIES;
	do
	{
		ADC_StartConversion();
		wrong_pass_flag = 0;
		LCD_Send_vCmd(CLEAR_SCREEN);
		LCD_vMove_Cursor(1,5);
		LCD_Send_vString("Trial ");
		LCD_Send_vChar(trial + '0');
		for (unsigned char i = 0; i < NUMBER_OF_PASSWORD; i++)
		{
			LED_vTurnOFF('c', 2);
			LCD_vMove_Cursor(2,1 + i);
			ADC_StartConversion();
			do
			{
				password =  Read_KeyPad();
				ADC_StartConversion();
			}while (password == NotPressed);
			LCD_Send_vChar(password);
			_delay_ms(80);
			LCD_vMove_Cursor(2,1 + i);
			LCD_Send_vChar('*');
			_delay_ms(80);
			if (password != EEPROM_8uRead(EEPROM_PASSWORD_LOCATION1 + i))
			{
				wrong_pass_flag = 1;
			}
		}
		if (wrong_pass_flag == 1)
		{
			trial--;
			LED_vTurnON('c', 2);
			_delay_ms(1000);
		}
	} while (trial != 0 && wrong_pass_flag == 1);
	
	ADC_StartConversion();
	
	if (wrong_pass_flag == 1)
	{
		return 0;
	} 
	else
	{
		return 1;
	}
}

void change_password ()
{
	unsigned char new, counter = 0,  new_pass[NUMBER_OF_PASSWORD];
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("Enter New PSW:");
	LCD_vMove_Cursor(2,1);
	while ((new =  Read_KeyPad()) != '=' && counter != NUMBER_OF_PASSWORD)
	{
		ADC_StartConversion();
		if (new != NotPressed)
		{
			LCD_Send_vChar(new);
			new_pass[counter] = new;
			counter++;
		}
	}
	_delay_ms(1500);
	for (unsigned char i = 0; i < NUMBER_OF_PASSWORD; i++)
	{
		EEPROM_vWrite(EEPROM_PASSWORD_LOCATION1 + i, new_pass[i]);
	}
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_Send_vString("PSW changed");
	LED_vTurnON('c', 4);
	_delay_ms(1500);
	LED_vTurnOFF('c', 4);
}

void With_Draw ()
{
	unsigned int sum;
	unsigned char withdr[10] = {0};
	unsigned char counter = 0, wd = 0;
	current_salary();
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("Enter Value:");
	LCD_vMove_Cursor(2,1);
	while ((wd =  Read_KeyPad()) != '=')
	{
		ADC_StartConversion();
		if (wd != NotPressed)
		{
			LCD_Send_vChar(wd);
			withdr[counter] = (wd - '0');
			counter++;
		}
	}
	
	DIO_vWRITE_PORT('d',0x0a);
	LED_vTurnON('c',3);
	_delay_ms(3000);
	DIO_vWRITE_PORT('d',0x00);
	LED_vTurnOFF('c',3);
	_delay_ms(3000);

	sum = withdr[0];
	for (unsigned char i = 1; i < counter; i++)
	{
		sum = sum*10 + withdr[i];
	}
	if (sum <= current_balance)
	{
		current_balance -= sum;
		current_salary();
	}
	else
	{
		LCD_Send_vCmd(CLEAR_SCREEN);
		LCD_vMove_Cursor(1,1);
		LCD_Send_vString("Your Money");
		LCD_vMove_Cursor(2,1);
		LCD_Send_vString("is not enough");
		_delay_ms(2000);
	}
	ADC_StartConversion();
}

void set_pass()
{
	if (EEPROM_8uRead(EEPROM_STATUS_LOCATION) != 0x00)
	{
		EEPROM_vWrite(EEPROM_PASSWORD_LOCATION1, '1');
		EEPROM_vWrite(EEPROM_PASSWORD_LOCATION2, '2');
		EEPROM_vWrite(EEPROM_PASSWORD_LOCATION3, '3');
		EEPROM_vWrite(EEPROM_PASSWORD_LOCATION4, '4');
		EEPROM_vWrite(EEPROM_STATUS_LOCATION,0x00);
	}
}

void intro_display()
{
	ADC_StartConversion();
	LCD_vMove_Cursor(1,6);
	LCD_Send_vString("Hello");
	LCD_vMove_Cursor(2,6);
	LCD_Send_vString("There!");
	_delay_ms(1000);
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,4);
	LCD_Send_vString("Welcome To");
	LCD_vMove_Cursor(2,4);
	LCD_Send_vString("VS system");
	_delay_ms(1000);
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("(-) Back");
	LCD_vMove_Cursor(2,1);
	LCD_Send_vString("(+) Login");
	_delay_ms(1000);
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_Send_vString("Enter Choice:");
	LCD_vMove_Cursor(2,1);
	ADC_StartConversion();
}

void system_open(void)
{
	ADC_StartConversion();
	LED_vTurnON('c', 4);
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("correct Password");
	LCD_vMove_Cursor(2,1);
	LCD_Send_vString("System Open!");
	_delay_ms(1500);
	LED_vTurnOFF('c', 4);
	ADC_StartConversion();
}

void incorrect_pass(void)
{
	ADC_StartConversion();
	LED_vTurnON('c', 2);
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("Incorrect PSW");
	LCD_vMove_Cursor(2,1);
	LCD_Send_vString("try after ");
	Timer2_OverFlow_Init_Interrupt();
	counter_sec = 5;
	while(counter_sec != 0)
	{
		ADC_StartConversion();
		LCD_vMove_Cursor(2,11);
		LCD_Send_vChar(counter_sec+'0');
	}
	LED_vTurnOFF('c', 2);
	ADC_StartConversion();
}

void warning (void)
{
	DIO_vWRITE_PORT('d',0x05);
	for(unsigned char i = 0; i < 10; i++)
	{
		LED_vTOGGLE('c', 2);
		_delay_ms(500);
	}
	LED_vTurnOFF('c', 2);
	DIO_vWRITE_PORT('d',0x00);
}

char login_back(void)
{
	ADC_StartConversion();
	char choice;
	do
	{
		choice = Read_KeyPad();
		ADC_StartConversion();
	} while (choice == NotPressed);
	LCD_vMove_Cursor(2,1);
	LCD_Send_vChar(choice);
	ADC_StartConversion();
	_delay_ms(1000)	;
	return choice;
}


void login (void)
{
	ADC_StartConversion();
	char check_psw;
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_Send_vString("Enter Password:");
	_delay_ms(1000);
	while(check_password() == 0)
	{
		ADC_StartConversion();
		incorrect_pass();
	}
	system_open();
	ADC_StartConversion();
	system_open_flag = 1;
}

char display_options(void)
{
	char option;
	ADC_StartConversion();
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("Enter Selection:");
	LCD_vMove_Cursor(2,1);
	LCD_Send_vString("1)DP   2)WD");
	_delay_ms(2000);
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("3)Balance");
	LCD_vMove_Cursor(2,1);
	LCD_Send_vString("4)Change PSW");
	_delay_ms(2000);
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("Enter Selection:");
	LCD_vMove_Cursor(2,1);
	do
	{
		option =  Read_KeyPad();
		ADC_StartConversion();
	}while (option == NotPressed);
	LCD_Send_vChar(option);
	_delay_ms(1000);
	ADC_StartConversion();
	return option;
}

char back_end(void)
{
	char choice;
	ADC_StartConversion();
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("(-) Back");
	LCD_vMove_Cursor(2,1);
	LCD_Send_vString("(+) End");
	_delay_ms(2000);
	LCD_Send_vCmd(CLEAR_SCREEN);
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("Enter Selection:");
	LCD_vMove_Cursor(2,1);
	do
	{
		choice =  Read_KeyPad();
		ADC_StartConversion();
	}while (choice == NotPressed);
	LCD_Send_vChar(choice);
	_delay_ms(1000);
	ADC_StartConversion();
	return choice;
}

void close_system(void)
{
	ADC_StartConversion();
	LCD_vMove_Cursor(1,1);
	LCD_Send_vString("Thanks For using");
	LCD_vMove_Cursor(2,1);
	LCD_Send_vString("our Services");
	ADC_StartConversion();
}

ISR(TIMER2_OVF_vect)
{
	counter_sec--;
}

