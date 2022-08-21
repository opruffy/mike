/*
 * lcd_body_graph.c
 *
 *  Created on: 15.03.2020
 *      Author: Patrick
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "buffer_lcd.h"
#include "calc.h"
#include "measure_period.h"

#include "lcd_matrix.h"
#include "lcd_pixel_settings.h"
#include "lcd_symbol.h"

#define ARROW_RIGHT					(0)
#define ARROW_UP					(1)
#define ARROW_DOWN					(2)

#define X_AXIS_INC_DISTANZ			(X_AXIS_LENGTH_X / 3)
#define Y_AXIS_INC_DISTANZ			(Y_AXIS_LENGTH_Y / 3)

#define LCD_GRAPH_BUFFER_SIZE		(X_AXIS_LENGTH_X)

buffer_info_t lcd_graph_buffer[LCD_GRAPH_BUFFER_SIZE] = { 0 };
uint8_t lcd_graph_index = 0;
uint8_t lcd_graph_index_changed = 0;
size_t data_length = 0;

// indices which are shown
uint8_t buffer_index[][2] =
{
	{
		0, 3,
	},
	{
		3, 6,
	},
	{
		6, 9,
	},
	{
		9, 12,
	},
};

char lcd_graph_buffer_string[][9] = {
		"ADC1-3",
		"ADC4-6",
		"ADC7-9",
		"ADC10-12",
};

char lcd_graph_adc_string[][6] = {
		"ADC1 ",
		"ADC2 ",
		"ADC3 ",
		"ADC4 ",
		"ADC5 ",
		"ADC6 ",
		"ADC7 ",
		"ADC8 ",
		"ADC9 ",
		"ADC10",
		"ADC11",
		"ADC12",
};

uint8_t arrow_axis[][ARROW_LENGTH_Y][ARROW_LENGTH_X]=
{
	{
		{ 0, 0, 1, 0, 0},
		{ 0, 0, 0, 1, 0},
		{ 1, 1, 1, 1, 1},
		{ 0, 0, 0, 1, 0},
		{ 0, 0, 1, 0, 0},
	},
	{
		{ 0, 0, 1, 0, 0},
		{ 0, 1, 1, 1, 0},
		{ 1, 0, 1, 0, 1},
		{ 0, 0, 1, 0, 0},
		{ 0, 0, 1, 0, 0},
	},
	{
		{ 0, 0, 1, 0, 0},
		{ 0, 0, 1, 0, 0},
		{ 1, 0, 1, 0, 1},
		{ 0, 1, 1, 1, 0},
		{ 0, 0, 1, 0, 0},
	},
};


static uint8_t lcd_axis_arrow(uint16_t x, uint16_t y, uint8_t i)
{
	for(uint16_t _y = 0; _y < ARROW_LENGTH_Y; _y++)
	{
		for(uint16_t _x = 0; _x < ARROW_LENGTH_X; _x++)
		{
			if(arrow_axis[i][_y][_x] == 1)
			{
				if(lcd_matrix_set_pixel(x + _x, y + _y))
				{
					return 1;
				}
			}
		}
	}

	return 0;
}

static void lcd_x_axis_name(uint16_t x, uint16_t y)
{
	lcd_symbol_string(x, y, "T[\xB0\x43]");
}

static void lcd_y_axis_name(uint16_t x, uint16_t y)
{
	lcd_symbol_string(x, y, "t[min]");
}

static void lcd_x_axis_inc(void)
{
	for(uint16_t i = X_AXIS_INC_DISTANZ; i <= X_AXIS_LENGTH_X; i += X_AXIS_INC_DISTANZ)
	{
		lcd_matrix_set_pixel(X_AXIS_INC_X + i, X_AXIS_INC_Y);
	}
}

static void lcd_y_axis_inc(void)
{
	for(uint16_t i = Y_AXIS_INC_DISTANZ; i <= Y_AXIS_LENGTH_Y; i += Y_AXIS_INC_DISTANZ)
	{
		lcd_matrix_set_pixel(Y_AXIS_INC_X, Y_AXIS_INC_Y - i);
	}
}

static void lcd_body_x_axis(void)
{
	for(uint16_t x = 0; x < (X_AXIS_ORIGIN_X - X_AXIS_START_X); x++)
	{
		lcd_matrix_set_pixel(X_AXIS_START_X + x, X_AXIS_ORIGIN_Y);
	}

	for(uint16_t x = 0; x < X_AXIS_LENGTH_X; x++)
	{
		lcd_matrix_set_pixel(X_AXIS_ORIGIN_X + x, X_AXIS_ORIGIN_Y);
	}
}

static void lcd_body_y_axis(void)
{
	for(uint16_t y = 0; y < (Y_AXIS_START_Y - Y_AXIS_ORIGIN_Y); y++)
	{
		lcd_matrix_set_pixel(Y_AXIS_ORIGIN_X, Y_AXIS_START_Y - y);
	}

	for(uint16_t y = 0; y < Y_AXIS_LENGTH_Y; y++)
	{
		lcd_matrix_set_pixel(Y_AXIS_ORIGIN_X, Y_AXIS_ORIGIN_Y - y);
	}
}

static void lcd_body_graph_set_x_axis(uint32_t x_axis, uint32_t _time)
{
	char tmp[6] = {0};
	uint32_t offset = 0;

	sprintf(tmp, "%lu", _time);

	if(_time < 10)
	{
		offset = 4;
	}
	else if(_time < 100)
	{
		offset = 7;
	}
	else if(_time < 1000)
	{
		offset = 10;
	}
	else if(_time < 10000)
	{
		offset = 13;
	}
	else
	{
		offset = 16;
	}

	lcd_symbol_string(x_axis - offset, 128 - 8, tmp);
}

#define round(x)    ((uint16_t) (x + .5))

static void lcd_body_graph_set_y_axis(uint32_t y_axis, float value)
{
	char tmp[4] = {0};
	uint32_t offset = 0;
	uint16_t round_value = round(value);

	sprintf(tmp, "%u", round_value);

	if(round_value < 10)
	{
		offset = 12;
	}
	else if(round_value < 100)
	{
		offset = 6;
	}
	else
	{
		offset = 0;
	}

	lcd_symbol_string(offset, y_axis, tmp);
}

static void lcd_body_graph_x_axis(void)
{
	uint32_t _time = 0;

	if(data_length < LCD_GRAPH_BUFFER_SIZE)
	{
		// initial max time in minutes for all measuring points in graph
		_time = measure_period_get_current_value() * LCD_GRAPH_BUFFER_SIZE / 600; // TODO 600 .. 60 sec->min; 10 msec->sec

		lcd_body_graph_set_x_axis(X_AXIS_ORIGIN_X + X_AXIS_INC_DISTANZ, _time / 3);
		lcd_body_graph_set_x_axis(X_AXIS_ORIGIN_X + X_AXIS_INC_DISTANZ * 2, _time * 2 / 3);
		lcd_body_graph_set_x_axis(X_AXIS_ORIGIN_X + X_AXIS_INC_DISTANZ * 3, _time);
	}
	else
	{
		_time = lcd_graph_buffer[data_length - 1].min + lcd_graph_buffer[data_length - 1].hour * 60;

		lcd_body_graph_set_x_axis(X_AXIS_ORIGIN_X + X_AXIS_INC_DISTANZ, _time - LCD_GRAPH_BUFFER_SIZE * 2 / 3);
		lcd_body_graph_set_x_axis(X_AXIS_ORIGIN_X + X_AXIS_INC_DISTANZ * 2, _time - LCD_GRAPH_BUFFER_SIZE / 3);
		lcd_body_graph_set_x_axis(X_AXIS_ORIGIN_X + X_AXIS_INC_DISTANZ * 3, _time);
	}
}

static void lcd_body_graph_y_axis(float max_value)
{
	lcd_body_graph_set_y_axis(Y_AXIS_ORIGIN_Y - Y_AXIS_INC_DISTANZ - 2, max_value / 3);
	lcd_body_graph_set_y_axis(Y_AXIS_ORIGIN_Y - Y_AXIS_INC_DISTANZ * 2 - 2, max_value * 2 / 3);
	lcd_body_graph_set_y_axis(Y_AXIS_ORIGIN_Y - Y_AXIS_INC_DISTANZ * 3 - 2, max_value);
}

static void lcd_body_graph_number(char* str)
{
	lcd_symbol_string(240 - 8*8, BODY_SUB_HOME_Y, str);		// TODO numbers
}

static void lcd_body_graph_adc_order(char* str, uint8_t _index)
{
	lcd_symbol_string(240 - 8*8, BODY_SUB_HOME_Y + LETTER_Y + _index * LETTER_Y , str);		// TODO numbers
}

static void lcd_body_graph_menu(uint8_t _index)
{
	lcd_axis_arrow(GRAPH_MENU_AXIS_UP_START_X, GRAPH_MENU_AXIS_UP_START_Y, ARROW_UP);

	for(uint16_t y = 0; y < GRAPH_MENU_AXIS_LENGTH; y++)
	{
		lcd_matrix_set_pixel(GRAPH_MENU_AXIS_START_X, y + GRAPH_MENU_AXIS_START_Y);
	}

	lcd_symbol_rect_filled(GRAPH_MENU_AXIS_START_X - 1, GRAPH_MENU_AXIS_START_Y + _index * GRAPH_MENU_CUBE_GAB, GRAPH_MENU_CUBE_LENGTH, GRAPH_MENU_CUBE_LENGTH);

	lcd_axis_arrow(GRAPH_MENU_AXIS_DOWN_START_X, GRAPH_MENU_AXIS_DOWN_START_Y, ARROW_DOWN);
}

static uint8_t lcd_body_graph_reset(void)
{
	lcd_matrix_reset(X_AXIS_ORIGIN_X, Y_AXIS_ORIGIN_Y - Y_AXIS_LENGTH_Y, X_AXIS_LENGTH_X , Y_AXIS_LENGTH_Y);

	return 0;
}

static void lcd_body_graph_diagram_draw(uint8_t _index)
{
	// TODO maximum_old merken, wenn es sich ändert, -> Reset Matrix

	float maximum = 0;
	uint8_t lcd_adc_order_index[3] = {0};

	for(uint32_t x = 0; x < data_length; x++)
	{
		for(uint32_t y = buffer_index[_index][0]; y < buffer_index[_index][1]; y++)
		{
			float value = calc_temp(lcd_graph_buffer[x].buffer[y]);

			if(maximum < value)
			{
				maximum = value;
			}
		}
	}
	// end calc maximum

	if(data_length)
	{
		// set index
		uint32_t x = buffer_index[_index][0];
		for(uint32_t y = 0; y < (sizeof(lcd_adc_order_index) / sizeof(lcd_adc_order_index[0])); y++)
		{
			lcd_adc_order_index[y] = x;
			x++;
		}

		// sort index
		for(uint32_t y = 1; y < (sizeof(lcd_adc_order_index) / sizeof(lcd_adc_order_index[0])); y++)
		{
			if(lcd_graph_buffer[data_length - 1].buffer[lcd_adc_order_index[y - 1]] < lcd_graph_buffer[data_length - 1].buffer[lcd_adc_order_index[y]])
			{
				uint8_t tmp = lcd_adc_order_index[y];
				lcd_adc_order_index[y] = lcd_adc_order_index[y - 1];
				lcd_adc_order_index[y - 1] = tmp;
			}
		}

		for(uint32_t y = 0; y < (sizeof(lcd_adc_order_index) / sizeof(lcd_adc_order_index[0])); y++)
		{
			lcd_body_graph_adc_order(lcd_graph_adc_string[lcd_adc_order_index[y]], y);
		}
	}

	for(uint32_t x = 0; x < data_length; x++)
	{
		for(uint32_t y = buffer_index[_index][0]; y < buffer_index[_index][1]; y++)
		{
			float value = calc_temp(lcd_graph_buffer[x].buffer[y]);

			lcd_matrix_set_pixel(X_AXIS_ORIGIN_X + x, Y_AXIS_ORIGIN_Y + 1 - (value * Y_AXIS_LENGTH_Y / maximum));
		}
	}

	lcd_body_graph_x_axis();
	lcd_body_graph_y_axis(maximum);
}

uint8_t lcd_body_graph_draw(void)
{
	lcd_body_x_axis();
	lcd_body_y_axis();

	lcd_axis_arrow(X_AXIS_ARROW_START_X, X_AXIS_ARROW_START_Y, ARROW_RIGHT);
	lcd_axis_arrow(Y_AXIS_ARROW_START_X, Y_AXIS_ARROW_START_Y, ARROW_UP);

	lcd_y_axis_name(X_AXIS_NAME_X, X_AXIS_NAME_Y);
	lcd_x_axis_name(Y_AXIS_NAME_X, Y_AXIS_NAME_Y);

	lcd_x_axis_inc();
	lcd_y_axis_inc();

	lcd_body_graph_diagram_draw(lcd_graph_index);
	lcd_body_graph_menu(lcd_graph_index);

	lcd_body_graph_number(lcd_graph_buffer_string[lcd_graph_index]);

	return 0;
}

uint8_t lcd_body_graph_update(void)
{
	size_t count = buffer_lcd_get_count();

	if(count > 0)
	{
		if(count >= LCD_GRAPH_BUFFER_SIZE)
		{
			count = LCD_GRAPH_BUFFER_SIZE;
			buffer_lcd_get_values(lcd_graph_buffer, count);
			data_length = count;
		}
		else
		{
			if((data_length + count) > LCD_GRAPH_BUFFER_SIZE)
			{
				memmove(&lcd_graph_buffer[0], &lcd_graph_buffer[0] + count, (LCD_GRAPH_BUFFER_SIZE - count) * sizeof(lcd_graph_buffer[0]));
				data_length = LCD_GRAPH_BUFFER_SIZE - count;
			}

			buffer_lcd_get_values(lcd_graph_buffer + data_length, count);
			data_length += count;
		}

		lcd_body_graph_reset();
		lcd_body_graph_diagram_draw(lcd_graph_index);

		lcd_graph_index_changed = 0;
	}
	else if(lcd_graph_index_changed)
	{
		lcd_body_graph_reset();
		lcd_body_graph_diagram_draw(lcd_graph_index);

		lcd_graph_index_changed = 0;
	}

	return 0;
}

uint8_t lcd_body_graph_trigger_up(void)
{
	if(lcd_graph_index == 0)
	{
		lcd_graph_index = sizeof(lcd_graph_buffer_string) / sizeof(lcd_graph_buffer_string[0]);
	}

	lcd_graph_index--;

	lcd_graph_index_changed = 1;
	return 0;
}

uint8_t lcd_body_graph_trigger_down(void)
{
	lcd_graph_index++;
	if(lcd_graph_index >= (sizeof(lcd_graph_buffer_string) / sizeof(lcd_graph_buffer_string[0])))
	{
		lcd_graph_index = 0;
	}

	lcd_graph_index_changed = 1;
	return 0;
}

void lcd_body_graph_stop(void)
{
	buffer_lcd_stop();
	data_length = 0;
}

