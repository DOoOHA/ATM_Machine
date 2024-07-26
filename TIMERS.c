/*
 * TIMERS.c
 *
 * Created: 2/8/2024 3:03:55 AM
 *  Author: DOoOHA
 */ 

#include "bitwise_macros.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void Timer0_CTC_Init_Interrupt(void)
{
	//Select CTC Mode
	CLR_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
	// Select Timer Clock
	SET_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS02);
	// Load a Value in OCR0
	OCR0 = 80; // ---> for each interrupt it takes 10mSec
	//Enable Interrupt
	sei();
	SET_BIT(TIMSK, OCIE0);
}

void Timer0_wave_nonPWM(void)
{
	//Set OC0 as output pin
	SET_BIT(DDRB,3);
	//Select CTC Mode
	CLR_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
	//Load a value in OCR0
	OCR0=64;
	// Select Timer Clock
	SET_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS02);
	//Toggle OC0 on Compare Match --> time peride almost = 8.3 mSec
	SET_BIT(TCCR0,COM00);
}

void Timer0_wave_FastPWM(void)
{
	//Set OC0 as output pin
	SET_BIT(DDRB,3);
	//Select CTC Mode
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);	
	//Load a value in OCR0
	OCR0=64;
	// Select Timer Clock
	SET_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS02);
	//Clear at compare match, Clear at overflow (non-inverting mode)
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
}

void Timer0_wave_PhaseCorrectPWM(void)
{
	//Set OC0 as output pin
	SET_BIT(DDRB,3);
	//Select CTC Mode
	SET_BIT(TCCR0, WGM00);
	CLR_BIT(TCCR0, WGM01);
	//Load a value in OCR0
	OCR0=64;
	// Select Timer Clock
	SET_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS02);
	//Clear at up-counting, Set at down-counting
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
}

void Timer2_OverFlow_Init_Interrupt(void)
{
	//Select OverFlow Mode
	CLR_BIT(TCCR2, WGM20);
	CLR_BIT(TCCR2, WGM21);
	// Select Clock Source to MUX Clock
	SET_BIT(ASSR, AS2);
	// Select Timer Clock For Each interrupt it takes 1 Sec
	SET_BIT(TCCR2, CS20);
	CLR_BIT(TCCR2, CS21);
	SET_BIT(TCCR2, CS22);
	//Enable Interrupt
	sei();
	SET_BIT(TIMSK, TOIE2);
}

void Timer1_wave_FastPWM(double value)
{
	//Set OC1A as output pin
	SET_BIT(DDRD,5);
	//Select fast PWM Mode
	SET_BIT(TCCR1A, WGM11);
	SET_BIT(TCCR1B, WGM12);
	SET_BIT(TCCR1B, WGM13);
	//Load a value in OCR0, ICR1
	OCR1A=value * 1000;
	ICR1 = 19999;
	// Select Timer Clock --> prescaler = 8 , Time periode = 1usec 
	CLR_BIT(TCCR1B, CS00);
	SET_BIT(TCCR1B, CS01);
	CLR_BIT(TCCR1B, CS02);
	//Clear at compare match, Clear at overflow (non-inverting mode)
	SET_BIT(TCCR1A,COM1A1);
}