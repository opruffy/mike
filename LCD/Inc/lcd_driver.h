/*
 * lcd_driver.h
 *
 *  Created on: 08.02.2020
 *      Author: Patrick
 */

#ifndef INC_LCD_DRIVER_H_
#define INC_LCD_DRIVER_H_

#include <stdint.h>

uint8_t lcd_data_write(uint8_t data);
uint8_t lcd_cmd_write(uint8_t cmd);

void lcd_reset(void);
void lcd_set_font(void);

#endif /* INC_LCD_DRIVER_H_ */
