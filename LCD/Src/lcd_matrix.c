/*
 * lcd_matrix.c
 *
 *  Created on: 15.03.2020
 *      Author: Patrick
 */

#include <stddef.h>

#include "lcd_function.h"
#include "lcd_display_view.h"

uint8_t matrix_current[128][(240 / 8)] = { 0 };
uint8_t matrix_new[128][(240 / 8)] = { 0 };


uint8_t lcd_matrix_set_pixel(uint16_t x, uint16_t y)
{
	x = lcd_display_view_get_x(x);
	y = lcd_display_view_get_y(y);

	matrix_new[y][(x / 8)] |= 1 << (x % 8);

	return 0;
}

uint8_t lcd_matrix_clear_pixel(uint16_t x, uint16_t y)
{
	x = lcd_display_view_get_x(x);
	y = lcd_display_view_get_y(y);

	matrix_new[y][(x / 8)] &= ~(1 << (x % 8));

	return 0;
}

uint8_t lcd_matrix_update(uint16_t x, uint16_t y, size_t x_length, size_t y_length)
{
	for(uint16_t _y = 0; _y < y_length; _y++)
	{
		for(uint16_t _x = 0; _x < x_length; _x++)
		{
			uint16_t tmp_x = lcd_display_view_get_x(x + _x);
			uint16_t tmp_y = lcd_display_view_get_y(y + _y);

			uint8_t px_new = matrix_new[tmp_y][(tmp_x / 8)] >> (tmp_x % 8);
			uint8_t px_current = matrix_current[tmp_y][(tmp_x / 8)] >> (tmp_x % 8);

			if((px_new & 0x01) != (px_current & 0x01))
			{
				if((px_new & 0x01) == 0x01)
				{
					lcd_set_pixel(tmp_x, tmp_y);
					matrix_current[tmp_y][(tmp_x / 8)] |= 1 << (tmp_x % 8);
				}
				else
				{
					lcd_clear_pixel(tmp_x, tmp_y);
					matrix_current[tmp_y][(tmp_x / 8)] &= ~(1 << (tmp_x % 8));
				}
			}
		}
	}

	return 0;
}

uint8_t lcd_matrix_reset(uint16_t x, uint16_t y, size_t x_length, size_t y_length)
{
	for(uint16_t _y = 0; _y < y_length; _y++)
	{
		uint16_t _x = 0;

		while(_x < x_length)
		{
			uint16_t tmp_x = lcd_display_view_get_x(x + _x);
			uint16_t tmp_y = lcd_display_view_get_y(y + _y);

			if(((tmp_x % 8) == 0) && ((x_length - tmp_x) >= 8) && lcd_display_view_is_original())	// TODO Pfusch! Problem ist, wenn beim flip Display dann alle Pixels gelöscht werden, obwohl es nicht notwendig ist.
			{
				matrix_new[tmp_y][(tmp_x / 8)] = 0;
				_x += 8;
			}
			else
			{
				matrix_new[tmp_y][(tmp_x / 8)] &= ~(1 << (tmp_x % 8));
				_x++;
			}
		}
	}

	return 0;
}
