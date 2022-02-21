/*
 * lcd_function.h
 *
 *  Created on: 08.03.2020
 *      Author: Patrick
 */

#ifndef INC_LCD_FUNCTION_H_
#define INC_LCD_FUNCTION_H_

#include <stdint.h>

uint8_t lcd_initialize(void);

uint8_t lcd_set_pixel(uint16_t x, uint16_t y);
uint8_t lcd_set_pixel_byte(uint16_t x, uint16_t y, uint8_t byte);

uint8_t lcd_clear_pixel(uint16_t x, uint16_t y);

#endif /* INC_LCD_FUNCTION_H_ */
