/*
 * 	State machine for reading position of the potentiometer
 *
 * 	Created: 2015-11-27 16:02:27
 *  Author: Philip Ekholm
 */

#include <avr/io.h>

#include "hmi/hmi.c"
#include "regulator/regulator.c"

static void setup_state_machine(void) {
	enum state 	current_state = MOTOR_OFF,
				next_state = MOTOR_OFF;
	uint8_t key, last_key, regulator = 0;

	while (1) {
		key = numkey_read();
		regulator;// = regulator_read();

		switch(current_state){
			case MOTOR_OFF:
				lcd_write_str("MOTOR OFF!");

				if (key == '3' && regulator == 0)
					next_state = MOTOR_ON_FORWARD;
				else if (key == '1' && regulator == 0)
					next_state = MOTOR_ON_BACKWARD;

				if (next_state != MOTOR_OFF)
					lcd_clear();
			break;

			case MOTOR_ON_FORWARD:
				lcd_write_str("FORWARD");

				if (key == '0' && key != last_key)
					next_state = MOTOR_OFF;
				else if (regulator > 0)
					next_state = MOTOR_RUNNING_FORWARD;

				if (next_state != MOTOR_ON_FORWARD)
					lcd_clear();
			break;

			case MOTOR_RUNNING_FORWARD:
				lcd_write_str("FORWARD");
				lcd_set_cursor_pos(1, 0);
				lcd_write_str("SPEED: ");

				if (key == '0' && key != last_key)
					next_state = MOTOR_OFF;

				if (next_state != MOTOR_RUNNING_FORWARD)
					lcd_clear();
			break;

			case MOTOR_ON_BACKWARD:
				lcd_write_str("BACKWARD");

				if (key == '0' && key != last_key)
					next_state = MOTOR_OFF;
				else if (regulator > 0)
					next_state = MOTOR_RUNNING_BACKWARD;

				if (next_state != MOTOR_ON_BACKWARD)
					lcd_clear();
			break;

			case MOTOR_RUNNING_BACKWARD:
				lcd_write_str("BACKWARD");
				lcd_set_cursor_pos(1, 0);
				lcd_write_str("SPEED: ");

				if (key == '0' && key != last_key)
					next_state = MOTOR_OFF;

				if (next_state != MOTOR_RUNNING_FORWARD)
					lcd_clear();
			break;

			default:
			break;
		}

		current_state = next_state;
		last_key = key;
	}
}

int main(void) {
	/* initialize HMI (LCD and numeric keyboard) */
	hmi_init();
	regulator_init();

	lcd_clear();

	setup_state_machine();

	/* Program should never return from the state machine */
	return 0;
}







