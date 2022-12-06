/*
 * lcd_body_value.c
 *
 *  Created on: 16.03.2020
 *      Author: Patrick
 */

#include <stdio.h>

#include "buffer_lcd.h"
#include "calc.h"

#include "lcd_matrix.h"
#include "lcd_menu_coord.h"
#include "lcd_symbol.h"

char value_string[][13] =
{
		"ADC 01", "ADC 02", "ADC 03", "ADC 04", "ADC 05", "ADC 06",
		"ADC 07", "ADC 08", "ADC 09", "ADC 10", "ADC 11", "ADC 12",
		"ADC 13",
};

buffer_info_t lcd_value_buffer[1] = { 0 };


static uint8_t __draw_values(void)
{
	for(uint8_t i = 0; i < 4; i++)
	{
		char tmp[10] = {0};

		uint16_t offset = i * (VALUE_INFO_LENGTH_Y + VALUE_BOX_SPACE);
		lcd_symbol_string(VALUE_COL1_TEXT_START_X, VALUE_COL1_TEXT_START_Y + offset, value_string[i]);

		float value = 0;

		switch (i)
		{
			case 0:
				value = calc_temp(lcd_value_buffer[0].buffer[0]);
				sprintf(tmp, "%.2f°C", value);
				break;
			case 1:
				sprintf(tmp, "%u", lcd_value_buffer[0].buffer[0]);
				break;
			case 2:
				value = calc_room_temp(lcd_value_buffer[0].buffer[12]);
				sprintf(tmp, "%.2f°C", value);
				break;
			case 3:
				sprintf(tmp, "%u", lcd_value_buffer[0].buffer[12]);
				break;
			default:
				break;
		}

		lcd_matrix_reset(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
		lcd_symbol_rect(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
		lcd_symbol_string(VALUE_COL1_NUMBER_START_X, VALUE_COL1_NUMBER_START_Y + offset, tmp);
	}

	return 0;
}


uint8_t lcd_body_value_draw(void)
{
	// initialize to the maximum value of hours to get the first value
	lcd_value_buffer[0].hour = 0xFF;

	if(!buffer_lcd_get_lastest_value(lcd_value_buffer))
	{
		__draw_values();
	}

	return 0;
}

uint8_t lcd_body_value_update(void)
{
	if(!buffer_lcd_get_lastest_value(lcd_value_buffer))
	{
		__draw_values();
		return 0;
	}

	return 1;
}
