/*
 *	Drivers for keyboard and LCD-screen
 *
 * 	Will print out a key selected on the keyboard and print it to the LCD.
 * 	Use # for clearing screen
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
	char last_key;
	char key;

	while(1) {
		key = numkey_read();

		if (key != NO_KEY && key != last_key){
			if(key == '#')
				lcd_clear();
			else
				lcd_write(CHR, key);
		}

		last_key = key;
	}
}





