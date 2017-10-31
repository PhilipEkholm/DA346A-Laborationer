/*
 * regulator.c
 *
 * This is the device driver for the manual motor speed regulator.
 *
 * Author:	Mathias Beckius
 * Date:	2014-12-08
 *
 * Modified by Mathias Beckius, 26 June 2015, for the course DA346A at
 * Malmo University.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "regulator.h"
#include "../common.h"

// for storage of ADC value from temperature sensor
			// UPPGIFT: Deklarera en 8-bitars variabel som lagrar värdet

/*
 * Interrupt Service Routine for the ADC.
 * The ISR will execute when a A/D conversion is complete.
 */
ISR(ADC_vect)
{
	// read ADC value
	
}

/*
 * Initialize the ADC and ISR.
 * ADC Resolution is 8-bit.
 */
void regulator_init(void)
{		
	// init A/D conversion
	ADMUX	|= 0;				// set reference voltage (internal 5V)
	ADMUX	|= 0;				// select Single Ended Input for ADC15
	ADCSRB	|= 0;				// ADC15 needs selection in a second place
	ADMUX	|= 0;				// left adjustment of ADC value
	
	ADCSRA |= 0;				// prescaler 128
	ADCSRA |= 0;				// enable Auto Trigger
	ADCSRA |= 0;				// enable Interrupt
	ADCSRA |= 0;				// enable ADC

	// disable digital input on ADC15
	DIDR2 = 0;
	
	// disable USB controller (to make interrupts possible)
	//USBCON = 0;
	// enable global interrupts
	sei();

	// start conversion
	ADCSRA |= 0;
}

/*
 * Returns the value of the regulator in percent: 0-100%
 * The tinkerkit potentiometer doesn't give a full 5V output,
 * therefore the maximum ADC value can't be 255.
 * If this isn't adjusted ~87-90% will be the output of this function.
 */
uint8_t regulator_read(void)
{
	uint8_t percentage;
	//add code here to read out current setting
	return percentage;
}