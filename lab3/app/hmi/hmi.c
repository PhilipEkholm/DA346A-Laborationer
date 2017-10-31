/*
 * hmi.c
 *
 * Functions for user interactions:
 *	- let the user enter numbers with the numeric keyboard
 *	- show messages on the LCD
 *
 * Author:	Mathias Beckius
 *
 * Date:	2014-11-28
 */

#include <string.h>

#include "hmi.h"

#include "../lcd/lcd.c"
#include "../numkey/numkey.c"
#include "../delay/delay.c"

#define ROW_1 1
#define BLANK_SPACE 0x20

static void str_to_uint16(char *, uint8_t, uint16_t *);

/*
 * Convert a string of number characters to a integer number.
 * Important! Error handling is NOT implemented!
 *
 * parameter:
 *	p_str: pointer to the string's first character
 *	length: length of the string (excluding termination character)
 *	p_nr: pointer to number variable, where converted number is written.
 */

static void str_to_uint16(char *p_str, uint8_t length, uint16_t *p_nr)
{
	uint16_t result = 0;
	uint16_t multiplier = 1;
	uint8_t ascii;
	uint8_t nr;
	uint8_t pos = length - 1;
	while (1) {
		// determine ascii code
		ascii = (uint8_t) *(p_str + pos);
		// determine number (0-9)
		nr = ascii - 48;
		// convert number and add to result
		result += nr * multiplier;

		multiplier *= 10;
		if (pos > 0) {
			pos--;
		} else {
			break;
		}
	}
	// return result from conversion
	*p_nr = result;
}

/*
 * Initialization of the HMI functions:
 *	- init numeric keyboard
 *	- init LCD
 */

void hmi_init(void)
{
	numkey_init();
	lcd_init();
}

/*
 * Let the user enter a 3-digit integer number.
 * The user enters a digit (0-9) and confirms the number with '#'.
 * A digit can be erased by pressing '*'.
 *
 * parameter:
 *	p_msg: pointer to the first character of the message
 *  p_int_nr: pointer to number variable, where the entered number is written
 *
 * return:
 *	number of digits (0-3)
 */

uint8_t input_int(char *p_msg, uint16_t *p_int_nr)
{
	uint8_t length = 0;
	const uint8_t max_length = 3;
	char numbers[max_length + 1];
	uint8_t key, last_key;

	lcd_clear();
	lcd_set_cursor_pos(0, 0);
	lcd_write_str(p_msg);
	lcd_set_cursor_pos(ROW_1, 0);

	while (1) {
		key = numkey_read();

		if (key != NO_KEY && key != last_key){
			/* Input number is done */
			if (key == '#') {
				break;
			}
			/* Erase digit */
			else if (key == '*') {
				if (length > 0) {
					lcd_set_cursor_pos(ROW_1, length-1);
					lcd_write(CHR, BLANK_SPACE);
					lcd_set_cursor_pos(ROW_1, length-1);
					length--;
				}
			}
			else if (key >= '0' && key <= '9' && length < max_length) {	// enter digit?
				lcd_write(CHR, key);
				numbers[length] = key;
				length++;
			}
		}

		last_key = key;
	};
	// terminate string
	numbers[length] = '\0';
	// if a number was entered...
	if (length > 0) {
		// convert number!
		str_to_uint16(numbers, length, p_int_nr);
	}
	// return the number of digits
	return length;
}

/*
 * Show a message on the LCD (for a number of seconds).
 * The first string is written on the first row,
 * the second string is written on the second row.
 *
 * parameter:
 *	p_str1: pointer to first character of the string.
 *	p_str2: pointer to first character of the string.
 *  delay_after_msg: number of seconds to wait after message is shown.
 */

void output_msg(char *p_str1, char *p_str2, uint8_t delay_after_msg)
{
	//lcd_set_cursor_mode(CURSOR_OFF);												finns?
	lcd_clear();
	lcd_set_cursor_pos(0, 0);
	lcd_write_str(p_str1);
	lcd_set_cursor_pos(1, 0);
	lcd_write_str(p_str2);
	delay_s(delay_after_msg);
}







