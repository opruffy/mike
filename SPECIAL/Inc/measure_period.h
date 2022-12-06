/*
 * measure_period.h
 *
 *  Created on: 13.07.2021
 *      Author: Patrick
 */

#ifndef INC_MEASURE_PERIOD_H_
#define INC_MEASURE_PERIOD_H_

#include <stdint.h>

// MEASURE PERIOD
uint32_t measure_period_get_current_value(void);
void measure_period_set_mode(uint8_t _index);
uint8_t measure_period_get_current_mode(void);
uint8_t measure_period_get_previous_mode(uint8_t _index);
uint8_t measure_period_get_next_mode(uint8_t _index);
char * measure_period_get_text(uint8_t _index);

// MEASURE PERIOD STATUS
void measure_period_set_status_waiting(void);

uint8_t measure_period_get_status_ready(void);

void measure_period_set_status_started(void);
uint8_t measure_period_get_status_started(void);

void measure_period_set_status_finished(void);
uint8_t measure_period_get_status_finished(void);

void measure_period_reset_status(void);

uint8_t measure_period_update_status(void);

#endif /* INC_MEASURE_PERIOD_H_ */
