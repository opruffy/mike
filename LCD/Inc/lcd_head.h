/*
 * lcd_head.h
 *
 *  Created on: 18.03.2020
 *      Author: Patrick
 */

#ifndef INC_LCD_HEAD_H_
#define INC_LCD_HEAD_H_

#include <stdint.h>

// DRAW
uint8_t lcd_head_draw_value(void);
uint8_t lcd_head_draw_graph(void);
uint8_t lcd_head_draw_settings(void);
uint8_t lcd_head_draw_debug(void);

// UPDATE
//uint8_t lcd_head_update_value(void);
//uint8_t lcd_head_update_graph(void);
//uint8_t lcd_head_update_settings(void);
//uint8_t lcd_head_update_debug(void);

// RESET
uint8_t lcd_head_reset(void);

#endif /* INC_LCD_HEAD_H_ */
