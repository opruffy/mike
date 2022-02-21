/*
 * lcd_display_view.c
 *
 *  Created on: 11.04.2020
 *      Author: Patrick
 */

#include "lcd_config.h"
#include "lcd_display_view.h"

#define LCD_DISPLAY_ORIGINAL		(0)
#define LCD_DISPLAY_FLIP			(1)

#define VALUE_X						(PIXELS_PER_LINE - 1)
#define VALUE_Y						(NUMBER_OF_LINES - 1)

uint8_t flip_mode = LCD_DISPLAY_FLIP;		// TODO change to original MODE.


uint8_t lcd_display_view_set_flip(void)
{
	flip_mode = LCD_DISPLAY_FLIP;

	return 0;
}

uint8_t lcd_display_view_reset_flip(void)
{
	flip_mode = LCD_DISPLAY_ORIGINAL;

	return 0;
}

uint8_t lcd_display_view_is_original(void)
{
	uint8_t tmp = 1;

	if(flip_mode != LCD_DISPLAY_ORIGINAL)
	{
		tmp = 0;
	}

	return tmp;
}

uint16_t lcd_display_view_get_x(uint16_t x)
{
	if(flip_mode == LCD_DISPLAY_FLIP)
	{
		x = VALUE_X - x;
	}

	return x;
}

uint16_t lcd_display_view_get_y(uint16_t y)
{
	if(flip_mode == LCD_DISPLAY_FLIP)
	{
		y = VALUE_Y - y;
	}

	return y;
}
