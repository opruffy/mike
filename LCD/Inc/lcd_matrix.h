/*
 * lcd_matrix.h
 *
 *  Created on: 15.03.2020
 *      Author: Patrick
 */

#ifndef INC_LCD_MATRIX_H_
#define INC_LCD_MATRIX_H_

#include <stddef.h>
#include <stdint.h>

uint8_t lcd_matrix_set_pixel(uint16_t x, uint16_t y);
uint8_t lcd_matrix_clear_pixel(uint16_t x, uint16_t y);
uint8_t lcd_matrix_update(uint16_t x, uint16_t y, size_t x_length, size_t y_length);
uint8_t lcd_matrix_reset(uint16_t x, uint16_t y, size_t x_length, size_t y_length);

#endif /* INC_LCD_MATRIX_H_ */
