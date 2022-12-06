/*
 * lcd_symbol.c
 *
 *  Created on: 15.03.2020
 *      Author: Patrick
 */

#include <string.h>

#include "lcd_custom_char.h"
#include "lcd_matrix.h"
#include "lcd_pixel_settings.h"


// RECT
void lcd_symbol_rect(uint16_t x, uint16_t y, size_t x_length, size_t y_length)
{
	for(size_t _x = 0; _x < x_length; _x++)
	{
		lcd_matrix_set_pixel(x + _x, y);
		lcd_matrix_set_pixel(x + _x, y + y_length - 1);
	}

	for(size_t _y = 0; _y < (y_length - 1); _y++)
	{
		lcd_matrix_set_pixel(x, y + _y);
		lcd_matrix_set_pixel(x + x_length - 1, y + _y);
	}
}

void lcd_symbol_rect_inv(uint16_t x, uint16_t y, size_t x_length, size_t y_length)
{
	for(size_t _x = 0; _x < x_length; _x++)
	{
		lcd_matrix_clear_pixel(x + _x, y);
		lcd_matrix_clear_pixel(x + _x, y + y_length - 1);
	}

	for(size_t _y = 0; _y < (y_length - 1); _y++)
	{
		lcd_matrix_clear_pixel(x, y + _y);
		lcd_matrix_clear_pixel(x + x_length - 1, y + _y);
	}
}

void lcd_symbol_rect_filled(uint16_t x, uint16_t y, size_t x_length, size_t y_length)
{
	for(size_t _x = 0; _x < x_length; _x++)
	{
		for(size_t _y = 0; _y < y_length; _y++)
		{
			lcd_matrix_set_pixel(x + _x, y + _y);
		}
	}
}

void lcd_symbol_rect_clear(uint16_t x, uint16_t y, size_t x_length, size_t y_length)
{
	for(size_t _x = 0; _x < x_length; _x++)
	{
		for(size_t _y = 0; _y < y_length; _y++)
		{
			lcd_matrix_clear_pixel(x + _x, y + _y);
		}
	}
}

// SYMBOL
static void set_symbol_in_matrix(uint16_t x, uint16_t y, uint8_t symbol[LETTER_Y][LETTER_X])
{
	for(size_t _y = 0; _y < LETTER_Y; _y++)
	{
		for(size_t _x = 0; _x < LETTER_X; _x++)
		{
			if(symbol[_y][_x] == 1)
			{
				lcd_matrix_set_pixel(x + _x, y + _y);
			}
			else
			{
				lcd_matrix_clear_pixel(x + _x, y + _y);
			}
		}
	}
}

static uint8_t get_symbol(uint8_t tmp[][LETTER_X], char data)
{
	if((data >= 'A') && (data <= 'Z'))
	{
		memcpy(tmp, &custom_char_upper[data - 'A'][0][0], LETTER_Y * LETTER_X);
	}
	else if((data >= 'a') && (data <= 'z'))
	{
		memcpy(tmp, &custom_char_lower[data - 'a'][0][0], LETTER_Y * LETTER_X);
	}
	else if((data >= '0') && (data <= '9'))
	{
		memcpy(tmp, &custom_nmb[data - '0'][0][0], LETTER_Y * LETTER_X);
	}
	else if(data == '.')
	{
		memcpy(tmp, &custom_symbol[SYMBOL_PUNKT][0][0], LETTER_Y * LETTER_X);
	}
	else if(data == ':')
	{
		memcpy(tmp, &custom_symbol[SYMBOL_DOPPELPUNKT][0][0], LETTER_Y * LETTER_X);
	}
//	else if(data == ' ')
//	{
//		;
//	}
	else if(data == 0xB0)	// '°'
	{
		memcpy(tmp, &custom_symbol[SYM_DEGREE][0][0], LETTER_Y * LETTER_X);
	}
	else if(data == '[')
	{
		memcpy(tmp, &custom_symbol[SYM_SQUARE_BRACKETS_LEFT][0][0], LETTER_Y * LETTER_X);
	}
	else if(data == ']')
	{
		memcpy(tmp, &custom_symbol[SYM_SQUARE_BRACKETS_RIGHT][0][0], LETTER_Y * LETTER_X);
	}
	else if(data == '-')
	{
		memcpy(tmp, &custom_symbol[SYM_HYPHEN][0][0], LETTER_Y * LETTER_X);
	}
	else
	{
		// got no symbol
		return 0;
	}

	return 1;
}

static void set_char_in_matrix(uint16_t x, uint16_t y, char data)
{
	uint8_t tmp[LETTER_Y][LETTER_X] = {0};

	if(get_symbol(tmp, data))
	{
		set_symbol_in_matrix(x, y, tmp);
	}
}

static void set_symbol_in_matrix_inv(uint16_t x, uint16_t y, uint8_t symbol[LETTER_Y][LETTER_X])
{
	for(size_t _y = 0; _y < LETTER_Y; _y++)
	{
		for(size_t _x = 0; _x < LETTER_X; _x++)
		{
			if(symbol[_y][_x] == 0)
			{
				lcd_matrix_set_pixel(x + _x, y + _y);
			}
			else
			{
				lcd_matrix_clear_pixel(x + _x, y + _y);
			}
		}
	}
}

static void set_char_in_matrix_inv(uint16_t x, uint16_t y, char data)
{
	uint8_t tmp[LETTER_Y][LETTER_X] = {0};

	if(get_symbol(tmp, data))
	{
		set_symbol_in_matrix_inv(x, y, tmp);
	}
}

void lcd_symbol_string(uint16_t x, uint16_t y, char* string)
{
	while(*string)
	{
		set_char_in_matrix(x, y, *string++);
		x += LETTER_X;
	}
}

void lcd_symbol_string_inv(uint16_t x, uint16_t y, char* string)
{
	while(*string)
	{
		set_char_in_matrix_inv(x, y, *string++);
		x += LETTER_X;
	}
}


/*
 * SYMBOL
 */
void lcd_symbol_symb(uint16_t x, uint16_t y, uint8_t index)
{
	for(size_t _y = 0; _y < LETTER_Y; _y++)
	{
		for(size_t _x = 0; _x < LETTER_X; _x++)
		{
			if(custom_symbol[index][_y][_x] == 1)
			{
				lcd_matrix_set_pixel(x + _x, y + _y);
			}
			else
			{
				lcd_matrix_clear_pixel(x + _x, y + _y);
			}
		}
	}
}

void lcd_symbol_symb_inv(uint16_t x, uint16_t y, uint8_t index)
{
	for(size_t _y = 0; _y < LETTER_Y; _y++)
	{
		for(size_t _x = 0; _x < LETTER_X; _x++)
		{
			if(custom_symbol[index][_y][_x] == 0)
			{
				lcd_matrix_set_pixel(x + _x, y + _y);
			}
			else
			{
				lcd_matrix_clear_pixel(x + _x, y + _y);
			}
		}
	}
}

void lcd_symbol_symb_clear(uint16_t x, uint16_t y)
{
	for(size_t _y = 0; _y < LETTER_Y; _y++)
	{
		for(size_t _x = 0; _x < LETTER_X; _x++)
		{
			lcd_matrix_clear_pixel(x + _x, y + _y);
		}
	}
}
