/*
 * clock.h
 *
 *  Created on: 13.06.2019
 *      Author: MT-LAB
 */

#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_

#include <stdint.h>

void clock_inc(void);

void clock_set_msec(uint8_t value);
void clock_set_sec(uint8_t value);
void clock_set_min(uint8_t value);
void clock_set_hour(uint8_t value);

void clock_reset(void);

uint8_t clock_get_msec(void);
uint8_t clock_get_sec(void);
uint8_t clock_get_min(void);
uint8_t clock_get_hour(void);

void clock_set_status(void);
uint8_t clock_get_status(void);
void clock_reset_status(void);

#endif /* INC_CLOCK_H_ */
