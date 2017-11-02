/*
 * regulator.h
 *
 * This is the device driver for the manual motor speed regulator.
 *
 * Author:	Mathias Beckius, Philip Ekholm
 *
 * Date:	2014-12-08
 */

#pragma once

#include <inttypes.h>

void regulator_init(void);
uint8_t regulator_read(void);
