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

	lcd_write_str("HELLO LEO");

	while(1) {

	}
}