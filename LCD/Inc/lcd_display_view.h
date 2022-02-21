/*
 * lcd_display_view.h
 *
 *  Created on: 11.04.2020
 *      Author: Patrick
 */

#ifndef INC_LCD_DISPLAY_VIEW_H_
#define INC_LCD_DISPLAY_VIEW_H_

#include <stdint.h>

uint8_t lcd_display_view_set_flip(void);
uint8_t lcd_display_view_reset_flip(void);
uint8_t lcd_display_view_is_original(void);
uint16_t lcd_display_view_get_x(uint16_t x);
uint16_t lcd_display_view_get_y(uint16_t y);

#endif /* INC_LCD_DISPLAY_VIEW_H_ */
