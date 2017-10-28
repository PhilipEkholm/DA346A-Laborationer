/*
 *	Drivers for keyboard and LCD-screen
 *
 * 	Created: 2016-11-01 14:42:40
 *  Author: Philip Ekholm
 */

#include <inttypes.h>
#include <stdio.h>

#include <avr/io.h>

#include "numkey/numkey.c"
#include "delay/delay.c"
#include "lcd/lcd.c"

int main(void)
{
	numkey_init();
	lcd_init();
	lcd_clear();

	DDRB = 0xFF;

	while(1) {
		PORTB = 0x00;
		delay_ms(250);
		delay_ms(250);
		PORTB = 0xFF;
		delay_ms(250);
		delay_ms(250);
	}
}