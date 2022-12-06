/*
 * lcd_symbol.h
 *
 *  Created on: 15.03.2020
 *      Author: Patrick
 */

#ifndef INC_LCD_SYMBOL_H_
#define INC_LCD_SYMBOL_H_

#include <stdint.h>
#include <stddef.h>

void lcd_symbol_rect(uint16_t x, uint16_t y, size_t x_length, size_t y_length);
void lcd_symbol_rect_inv(uint16_t x, uint16_t y, size_t x_length, size_t y_length);

void lcd_symbol_rect_filled(uint16_t x, uint16_t y, size_t x_length, size_t y_length);
void lcd_symbol_rect_clear(uint16_t x, uint16_t y, size_t x_length, size_t y_length);

void lcd_symbol_string(uint16_t x, uint16_t y, char* string);
void lcd_symbol_string_inv(uint16_t x, uint16_t y, char* string);

void lcd_symbol_symb(uint16_t x, uint16_t y, uint8_t index);
void lcd_symbol_symb_inv(uint16_t x, uint16_t y, uint8_t index);
void lcd_symbol_symb_clear(uint16_t x, uint16_t y);

#endif /* INC_LCD_SYMBOL_H_ */
