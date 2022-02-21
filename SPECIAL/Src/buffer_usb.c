/*
 * buffer_usb.c
 *
 *  Created on: 01.12.2020
 *      Author: Patrick
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "buffer.h"
#include "clock.h"
#include "debug.h"

#define BUFFER_USB_COUNT	20

buffer_info_t buffer_usb[BUFFER_USB_COUNT] = { 0 };
size_t buffer_usb_w_index = 0;
size_t buffer_usb_r_index = 0;
uint8_t buffer_usb_overflow_data = 0;

uint8_t buffer_usb_state = 0;


static uint8_t buffer_usb_lock(uint8_t value)
{
	if(buffer_usb_state != 0)
	{
		return 1;
	}

	buffer_usb_state = value;
	return 0;
}

static uint8_t buffer_usb_unlock(void)
{
	buffer_usb_state = 0;
	return 0;
}

size_t buffer_usb_get_count(void)
{
	size_t count = 0;
	size_t offset = (buffer_usb_overflow_data == 1) ? (BUFFER_USB_COUNT) : (0);

	if((buffer_usb_w_index + offset) >= buffer_usb_r_index)
	{
		count = buffer_usb_w_index + offset - buffer_usb_r_index;
	}

	return count;
}

uint8_t buffer_usb_set_value(uint32_t *value, size_t length)	// length = adc values count??
{
	if(buffer_usb_lock(1))
	{
		return 1;
	}

	// increase the 'read index' to overwrite old data todo not allowed
	if((buffer_usb_overflow_data == 1) && (buffer_usb_w_index == buffer_usb_r_index))
	{
		return 2;
	}

	memcpy(buffer_usb[buffer_usb_w_index].buffer, value, length * sizeof(buffer_usb[0].buffer[0]));
	buffer_usb[buffer_usb_w_index].sec = clock_get_sec();
	buffer_usb[buffer_usb_w_index].min = clock_get_min();
	buffer_usb[buffer_usb_w_index].hour = clock_get_hour();

	buffer_usb_w_index++;
	debug_inc_usb_buffer_count();
	debug_set_usb_buffer_w_index(buffer_usb_w_index);

	if(buffer_usb_w_index == BUFFER_USB_COUNT)
	{
		buffer_usb_w_index = 0;
		buffer_usb_overflow_data = 1;
	}

	buffer_usb_unlock();
	return 0;
}

size_t buffer_usb_get_values(buffer_info_t* buffer, size_t count)
{
	if(buffer_usb_lock(2))
	{
		return 0;
	}

	if(count > buffer_usb_get_count())
		count = buffer_usb_get_count();

	if(count > 0)
	{
		size_t offset = 0;
		size_t offset_count = count;

		if(buffer_usb_overflow_data)
		{
			if(buffer_usb_r_index > buffer_usb_w_index)
			{
				offset = BUFFER_USB_COUNT - buffer_usb_r_index;
				memcpy(buffer, &buffer_usb[buffer_usb_r_index], offset * sizeof(buffer_usb[0]));
				offset_count -= offset;

				buffer_usb_r_index = 0;
				buffer_usb_overflow_data = 0;
			}
			else
			{
				// TODO miss error
			}
		}

		if(!buffer_usb_overflow_data && offset_count)
		{
			memcpy(buffer + offset, &buffer_usb[buffer_usb_r_index], offset_count * sizeof(buffer_usb[0]));
			buffer_usb_r_index += offset_count;
		}

		debug_set_usb_buffer_r_index(buffer_usb_r_index);
	}

	buffer_usb_unlock();
	return count;
}

void buffer_usb_reset_counter(void)
{
	buffer_usb_w_index = 0;
	buffer_usb_r_index = 0;

	buffer_usb_overflow_data = 0;
}

