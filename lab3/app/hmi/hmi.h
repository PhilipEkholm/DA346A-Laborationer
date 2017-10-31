/*
 * 	hmi.h
 *
 * 	Created: 2015-11-27 16:19:19
 *  Author: Philip Ekholm
 */

#pragma once

#include <inttypes.h>

void hmi_init(void);
uint8_t input_int(char *, uint16_t *);
void output_msg(char *, char *, uint8_t);
