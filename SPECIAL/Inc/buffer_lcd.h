/*
 * buffer_lcd.h
 *
 *  Created on: 01.12.2020
 *      Author: Patrick
 */

#ifndef INC_BUFFER_LCD_H_
#define INC_BUFFER_LCD_H_

#include "buffer.h"

size_t buffer_lcd_get_count(void);
uint8_t buffer_lcd_set_value(uint32_t *value, size_t length);
uint8_t buffer_lcd_get_values(buffer_info_t* buffer, size_t count);
uint8_t buffer_lcd_get_last_values(buffer_info_t* buffer);

void buffer_lcd_stop(void);

#endif /* INC_BUFFER_LCD_H_ */
