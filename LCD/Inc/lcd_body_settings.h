/*
 * lcd_body_settings.h
 *
 *  Created on: 16.03.2020
 *      Author: Patrick
 */

#ifndef INC_LCD_BODY_SETTINGS_H_
#define INC_LCD_BODY_SETTINGS_H_

#include <stdint.h>

uint8_t lcd_body_settings_start_trigger_ok(void);
uint8_t lcd_body_settings_start_draw(void);
uint8_t lcd_body_settings_start_update(void);

uint8_t lcd_body_settings_pause_trigger_ok(void);
uint8_t lcd_body_settings_pause_draw(void);
uint8_t lcd_body_settings_pause_update(void);

uint8_t lcd_body_settings_stop_trigger_ok(void);
uint8_t lcd_body_settings_stop_draw(void);
uint8_t lcd_body_settings_stop_update(void);

uint8_t lcd_body_settings_period_trigger_left(void);
uint8_t lcd_body_settings_period_trigger_right(void);
uint8_t lcd_body_settings_period_trigger_ok(void);
uint8_t lcd_body_settings_period_draw(void);
uint8_t lcd_body_settings_period_trigger_draw(void);
uint8_t lcd_body_settings_period_update(void);

uint8_t lcd_body_settings_flip_trigger_ok(void);
uint8_t lcd_body_settings_flip_draw(void);
uint8_t lcd_body_settings_flip_update(void);

#endif /* INC_LCD_BODY_SETTINGS_H_ */
