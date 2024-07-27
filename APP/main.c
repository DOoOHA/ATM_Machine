/*
 * main.c
 *
 * Created: 6/27/2024 12:33:17 AM
 *  Author: DOoOHA
 */ 


#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "app.h"
char system_open_flag = 0;

int main(void)
{
	char choice, option;
	modules_init();
	set_pass();
	intro_display();
	choice = login_back();
	switch(choice)
	{
		case  '+':
		login();
		break;
		case  '-':
		close_system();
		break;
	}
	
	while(system_open_flag == 1)
	{
		option = display_options();
		switch(option)
		{
			case  '1':
			deposit();
			break;
			case  '2':
			With_Draw();
			break;
			case  '3':
			current_salary();
			break;
			case  '4':
			change_password();
			break;
		}
		choice = back_end();
		if (choice == '+')
		{
			close_system();
			return 0;
		}
	}
}