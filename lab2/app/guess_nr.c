/*
 * 	guess_nr.c
 *
 * 	Game logic for playing the game
 *
 * 	Created: 2015-11-27 16:29:29
 *  Author: Philip Ekholm
 */

#include <stdio.h>
#include "guess_nr.h"
#include "hmi/hmi.h"

/* TODO: Remove prototypes */

static uint16_t get_nr(void);
static uint8_t playing_game(uint16_t, uint16_t *);
static void show_result(uint16_t);

/*
 * Let the user make a guess by entering a number.
 * The function never exists before the user has entered a number
 * between 1-100.
 *
 * return:
 *	the number that were entered by the user.
 */

static uint16_t get_nr(void)
{
	uint16_t guessed_nr;
	uint16_t input_length;

	while (1) {
		input_length = input_int("ENTER A NUMBER", &guessed_nr);
		/* if the user entered a number, and if it was between 1 and 100... */
		if (input_length > 0 && guessed_nr >= 1 && guessed_nr <= 100) {
			// ...return that number!
			return guessed_nr;
		} else {
			// show error/info message!
			output_msg("ENTER A NUMBER", "BETWEEN 1-100!", 1);
		}
	}
}

/*
 * Playing game, until the correct number is guessed!
 *
 * parameter:
 *	rnd_nr: random number (to be guessed)
 *	p_nr_of_guesses: pointer to variable with the current number of guesses
 * return:
 *	Returns 1 if the game should continue, 0 if the game is over.
 */

static uint8_t playing_game(uint16_t rnd_nr, uint16_t *p_nr_of_guesses)
{
	uint16_t guessed_nr;

	// let the user guess a number
	guessed_nr = get_nr();
	// keep track of number of guesses
	(*p_nr_of_guesses)++;

	// if the guessed number was the correct number...
	if (guessed_nr == rnd_nr) {
		output_msg("CORRECT NUMBER!", "", 1);
		return 0;	// return 0 for "game over!"
	} else if (guessed_nr < rnd_nr) { // number too low?
		output_msg("TOO LOW!", "", 1);
	} else { // number too high?
		output_msg("TOO HIGH!", "", 1);
	}
	return 1;		// return 1 for "keep on playing!"
}



/*
 * Show result (when the game has ended!)
 *
 * parameter:
 *	nr_of_guesses:	the number of guesses that was required
 *					to guess the correct number.
 */

static void show_result(uint16_t nr_of_guesses)
{
	char result[17];
	// show result
	sprintf(result, "GUESSES: %u", nr_of_guesses);
	output_msg(result, "", 3);
	if (nr_of_guesses <= 7) {
		output_msg("GOOD JOB!", "", 3);
	} else {
		output_msg("BETTER LUCK", "NEXT TIME...", 3);
	}
}

/*
 * Play a round of "Guess the number".
 *
 * parameter:
 *	rnd_nr: random number (to be guessed)
 */

void play_guess_nr(uint16_t rnd_nr)
{
	uint16_t nr_of_guesses = 0;
	// show initial message, before game starts.
	output_msg("CAN YOU GUESS", "THE NUMBER?", 3);
	// play game until the correct number is guessed!
	while (playing_game(rnd_nr, &nr_of_guesses));
	// show result!
	show_result(nr_of_guesses);
}















