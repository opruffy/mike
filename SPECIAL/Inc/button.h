/*
 * button.h
 *
 *  Created on: 17.03.2020
 *      Author: Patrick
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdint.h>

uint8_t button_get_pressed_any(void);
uint8_t button_get_pressed_up(void);
uint8_t button_get_pressed_down(void);
uint8_t button_get_pressed_left(void);
uint8_t button_get_pressed_right(void);
uint8_t button_get_pressed_ok(void);

#endif /* INC_BUTTON_H_ */
