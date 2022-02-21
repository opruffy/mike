/*
 * lcd_body_debug.c
 *
 *  Created on: 04.04.2020
 *      Author: Patrick
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "debug.h"
#include "lcd_matrix.h"
#include "lcd_menu_coord.h"
#include "lcd_symbol.h"
#include "usb_file.h"

size_t diff_index = 0;


uint8_t lcd_body_debug_draw(void)
{
	char tmp[10] = {0};
	uint16_t offset = 0;

	// LCD
	lcd_symbol_string(VALUE_COL1_TEXT_START_X, VALUE_COL1_TEXT_START_Y + offset, "LCD");

	sprintf(tmp, "%u", debug_get_lcd_buffer());

	lcd_matrix_reset(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_rect(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_string(VALUE_COL1_NUMBER_START_X, VALUE_COL1_NUMBER_START_Y + offset, tmp);

	// USB BUFFER
	offset = 1 * (VALUE_INFO_LENGTH_Y + VALUE_BOX_SPACE);
	lcd_symbol_string(VALUE_COL1_TEXT_START_X, VALUE_COL1_TEXT_START_Y + offset, "USB BU");

	sprintf(tmp, "%u", debug_get_usb_buffer_count());

	lcd_matrix_reset(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_rect(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_string(VALUE_COL1_NUMBER_START_X, VALUE_COL1_NUMBER_START_Y + offset, tmp);

	// USB ACCESS
	offset = 2 * (VALUE_INFO_LENGTH_Y + VALUE_BOX_SPACE);
	lcd_symbol_string(VALUE_COL1_TEXT_START_X, VALUE_COL1_TEXT_START_Y + offset, "USB AC");

	sprintf(tmp, "%u", debug_get_usb_access());

	lcd_matrix_reset(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_rect(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_string(VALUE_COL1_NUMBER_START_X, VALUE_COL1_NUMBER_START_Y + offset, tmp);

	// FILENAME
	offset = 3 * (VALUE_INFO_LENGTH_Y + VALUE_BOX_SPACE);
	lcd_symbol_string(VALUE_COL1_TEXT_START_X, VALUE_COL1_TEXT_START_Y + offset, "USB");

	lcd_matrix_reset(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_string(VALUE_COL1_NUMBER_START_X, VALUE_COL1_NUMBER_START_Y + offset, usb_file_get_filename());

	// USB BYTECOUNT
	offset = 4 * (VALUE_INFO_LENGTH_Y + VALUE_BOX_SPACE);
	lcd_symbol_string(VALUE_COL1_TEXT_START_X, VALUE_COL1_TEXT_START_Y + offset, "USB BC");

	sprintf(tmp, "%u", debug_get_usb_max_bytecount());

	lcd_matrix_reset(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_rect(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_string(VALUE_COL1_NUMBER_START_X, VALUE_COL1_NUMBER_START_Y + offset, tmp);

	// USB BUFFER W INDEX
	offset = 5 * (VALUE_INFO_LENGTH_Y + VALUE_BOX_SPACE);
	lcd_symbol_string(VALUE_COL1_TEXT_START_X, VALUE_COL1_TEXT_START_Y + offset, "USB BW");

	sprintf(tmp, "%u", debug_get_usb_buffer_w_index());

	lcd_matrix_reset(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_rect(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_string(VALUE_COL1_NUMBER_START_X, VALUE_COL1_NUMBER_START_Y + offset, tmp);

	// USB BUFFER R INDEX
	offset = 6 * (VALUE_INFO_LENGTH_Y + VALUE_BOX_SPACE);
	lcd_symbol_string(VALUE_COL1_TEXT_START_X, VALUE_COL1_TEXT_START_Y + offset, "USB BR");

	sprintf(tmp, "%u", debug_get_usb_buffer_r_index());

	lcd_matrix_reset(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_rect(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_string(VALUE_COL1_NUMBER_START_X, VALUE_COL1_NUMBER_START_Y + offset, tmp);

	// USB BUFFER DIFF INDEX
	offset = 7 * (VALUE_INFO_LENGTH_Y + VALUE_BOX_SPACE);
	lcd_symbol_string(VALUE_COL1_TEXT_START_X, VALUE_COL1_TEXT_START_Y + offset, "USB DI");

	size_t w_index = debug_get_usb_buffer_count();
	size_t r_index = debug_get_usb_access();

	if(w_index != r_index)
	{
		if(!diff_index)
		{
			diff_index = w_index;
		}
	}
	else
	{
		diff_index = 0;
	}

	sprintf(tmp, "%u", diff_index);

	lcd_matrix_reset(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_rect(VALUE_COL1_RECT_START_X, VALUE_COL1_RECT_START_Y + offset, VALUE_RECT_LENGTH_X, VALUE_RECT_LENGTH_Y);
	lcd_symbol_string(VALUE_COL1_NUMBER_START_X, VALUE_COL1_NUMBER_START_Y + offset, tmp);

	return 0;
}

uint8_t lcd_body_debug_update(void)
{
	lcd_body_debug_draw();

	return 0;
}
