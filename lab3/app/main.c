/*
 * 	State machine for reading position of the potentiometer
 *
 * 	Created: 2015-11-27 16:02:27
 *  Author: Philip Ekholm
 */
#include <stdio.h>

#include <avr/io.h>

#include "hmi/hmi.c"
#include "regulator/regulator.c"

static void setup_state_machine(void) {
	enum state 	current_state = MOTOR_OFF,
				next_state = MOTOR_OFF;
	uint8_t key, last_key, regulator = 0;

	char regulator_str[15];

	while (1) {
		key = numkey_read();
		regulator = regulator_read();

		switch(current_state){
			case MOTOR_OFF:
				output_msg("MOTOR OFF!", "", 0);

				if (key == '3' && regulator == 0)
					next_state = MOTOR_ON_FORWARD;
				else if (key == '1')
					next_state = MOTOR_ON_BACKWARD;

			break;

			case MOTOR_ON_FORWARD:
				output_msg("FORWARD", "", 0);

				if (key == '0' && key != last_key)
					next_state = MOTOR_OFF;
				else if (regulator > 0)
					next_state = MOTOR_RUNNING_FORWARD;
			break;

			case MOTOR_RUNNING_FORWARD:
				sprintf(regulator_str, "SPEED: %u%%", regulator);
				output_msg("FORWARD", regulator_str, 0);

				if (key == '0' && key != last_key)
					next_state = MOTOR_OFF;
			break;

			case MOTOR_ON_BACKWARD:
				output_msg("BACKWARD", "", 0);

				if (key == '0' && key != last_key)
					next_state = MOTOR_OFF;
				else if (regulator > 0)
					next_state = MOTOR_RUNNING_BACKWARD;
			break;

			case MOTOR_RUNNING_BACKWARD:
				sprintf(regulator_str, "SPEED: %u%%", regulator);
				output_msg("BACKWARD", regulator_str, 0);

				if (key == '0' && key != last_key)
					next_state = MOTOR_OFF;
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







