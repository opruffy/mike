/*
 * measure.h
 *
 *  Created on: 11.04.2020
 *      Author: Patrick
 */

#ifndef INC_MEASURE_H_
#define INC_MEASURE_H_

#include <stdint.h>

// MEASURE MODE STATUS
void measure_mode_status_set_changed(void);
uint8_t measure_mode_status_get_changed(void);
void measure_mode_status_update(void);

// MEASURE MODE
void measure_set_mode_start(void);
uint8_t measure_get_mode_start(void);

void measure_set_mode_running(void);
uint8_t measure_get_mode_running(void);

void measure_set_mode_pause(void);
uint8_t measure_get_mode_pause(void);

void measure_set_mode_stop(void);
uint8_t measure_get_mode_stop(void);

#endif /* INC_MEASURE_H_ */
