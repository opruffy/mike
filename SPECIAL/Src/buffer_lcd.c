/*
 * buffer_lcd.c
 *
 *  Created on: 12.05.2020
 *      Author: Patrick
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "buffer.h"
#include "clock.h"
#include "debug.h"

#define BUFFER_LCD_COUNT	100

buffer_info_t buffer_lcd[BUFFER_LCD_COUNT] = { 0 };
uint32_t buffer_lcd_w_index = 0;
uint32_t buffer_lcd_r_index = 0;
uint8_t buffer_lcd_overflow_data = 0;
uint8_t buffer_lcd_overflow_time = 0;

uint8_t buffer_lcd_state = 0;


static uint8_t buffer_lcd_lock(uint8_t value)
{
	if(buffer_lcd_state != 0)
	{
		return 1;
	}

	buffer_lcd_state = value;
	return 0;
}

static uint8_t buffer_lcd_unlock(void)
{
	buffer_lcd_state = 0;
	return 0;
}

size_t buffer_lcd_get_count(void)
{
	size_t count = 0;
	size_t offset = (buffer_lcd_overflow_data == 1) ? (BUFFER_LCD_COUNT) : (0);

	if((buffer_lcd_w_index + offset) >= buffer_lcd_r_index)
	{
		count = buffer_lcd_w_index + offset - buffer_lcd_r_index;
	}

	return count;
}

uint8_t buffer_lcd_set_value(uint32_t *value, size_t length)	// length = adc values count??
{
	if(buffer_lcd_lock(1))
	{
		return 1;
	}

	// increase the 'read index' to overwrite old data
	if((buffer_lcd_overflow_data == 1) && (buffer_lcd_w_index == buffer_lcd_r_index))
	{
		buffer_lcd_r_index++;

		if(buffer_lcd_r_index == BUFFER_LCD_COUNT)
		{
			buffer_lcd_r_index = 0;
		}
	}

	memcpy(buffer_lcd[buffer_lcd_w_index].buffer, value, length * sizeof(buffer_lcd[0].buffer[0]));
	buffer_lcd[buffer_lcd_w_index].sec = clock_get_sec();
	buffer_lcd[buffer_lcd_w_index].min = clock_get_min();
	buffer_lcd[buffer_lcd_w_index].hour = clock_get_hour();

	buffer_lcd_w_index++;
	debug_inc_lcd_buffer();

	if(buffer_lcd_w_index == BUFFER_LCD_COUNT)
	{
		buffer_lcd_w_index = 0;
		buffer_lcd_overflow_data = 1;
		buffer_lcd_overflow_time = 1;
	}

	buffer_lcd_unlock();
	return 0;
}

uint8_t buffer_lcd_get_values(buffer_info_t* buffer, size_t count)
{
	if(buffer_lcd_lock(2))
	{
		return 1;
	}

	if(buffer_lcd_get_count() >= count)
	{
		size_t length = (buffer_lcd_overflow_data == 1) ? (BUFFER_LCD_COUNT) : (0);
		buffer_lcd_r_index = buffer_lcd_w_index + length - count;

		size_t offset = 0;

		if(buffer_lcd_r_index > buffer_lcd_w_index)
		{
			offset = BUFFER_LCD_COUNT - buffer_lcd_r_index;
			memcpy(buffer, &buffer_lcd[buffer_lcd_r_index], offset * sizeof(buffer_lcd[0]));
			count -= offset;

			buffer_lcd_r_index = 0;
			buffer_lcd_overflow_data = 0;
		}

		memcpy(buffer + offset, &buffer_lcd[buffer_lcd_r_index], count * sizeof(buffer_lcd[0]));
		buffer_lcd_r_index += count;
	}

	buffer_lcd_unlock();
	return 0;
}

uint8_t buffer_lcd_get_lastest_value(buffer_info_t* buffer)
{
	size_t _index = 0;

	if(buffer_lcd_w_index == 0)
	{
		if(buffer_lcd_overflow_time == 1)
		{
			_index = BUFFER_LCD_COUNT - 1;
		}
		else
		{
			_index = 0;
		}
	}
	else
	{
		_index = buffer_lcd_w_index - 1;
	}

	if(	(buffer_lcd[_index].sec != buffer[0].sec)
		|| (buffer_lcd[_index].min != buffer[0].min)
		|| (buffer_lcd[_index].hour != buffer[0].hour))
	{
		memcpy(buffer, &buffer_lcd[_index], sizeof(buffer_lcd[0]));
		return 0;
	}

	return 1;
}

void buffer_lcd_stop(void)
{
	buffer_lcd_w_index = 0;
	buffer_lcd_r_index = 0;
	buffer_lcd_overflow_data = 0;
	buffer_lcd_overflow_time = 0;

	buffer_lcd_unlock();
}
