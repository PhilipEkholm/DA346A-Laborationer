/*
 * regulator.h
 *
 * This is the device driver for the manual motor speed regulator.
 *
 * Author:	Mathias Beckius
 *
 * Date:	2014-12-08
 */ 

#ifndef TEMP_H_
#define TEMP_H_

#include <inttypes.h>

void regulator_init(void);
uint8_t regulator_read(void);

#endif