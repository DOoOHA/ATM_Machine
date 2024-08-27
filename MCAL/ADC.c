/*
 * ADC.c
 *
 * Created: 1/27/2024 3:02:25 AM
 *  Author: DOoOHA
 */ 

#define VREF 2.56 //internal Vref (V)
#define LEVELS 1024
#define STEPS ((VREF / LEVELS) * 1000) //(mV)
#define TRANSDUCER 10   //(mV)

#include <avr/io.h>
#include <avr/interrupt.h>
#include "bitwise_macros.h"
#include "../APP/app.h"

volatile unsigned char temperature;
volatile float adc_result;
volatile unsigned short volt;

void ADC_Init()
{
	//Enable ADC
	SET_BIT(ADCSRA, ADEN);
	//Configure Vref
	SET_BIT(ADMUX, REFS0);
	SET_BIT(ADMUX, REFS1);
	//ADC Clock
	SET_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS2);
	// Enable ADC interrupt
	SET_BIT(ADCSRA, ADIE);
	// Enable global interrupts
	sei();
}

void ADC_StartConversion()
{
	// Start ADC conversion
	SET_BIT(ADCSRA, ADSC);
}

ISR(ADC_vect)
{
	// Read the ADC result
	adc_result = ADC;
	
	// Calculate temperature in Celsius (assuming 10mV per degree and Vref = 2.56V)
	volt = STEPS * adc_result;
	temperature = volt / TRANSDUCER;
	
	if (temperature > 30)
	{
		warning();
	}
}
