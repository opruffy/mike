/*
 * debug.c
 *
 *  Created on: 27.03.2021
 *      Author: Patrick
 */

#include <stddef.h>

size_t debug_usb_buffer_count = 0;
size_t debug_usb_buffer_w_index = 0;
size_t debug_usb_buffer_r_index = 0;
size_t debug_usb_access_count = 0;
size_t debug_lcd_buffer_count = 0;
size_t debug_max_usb_bytecount = 0;


void debug_reset_counter(void)
{
	debug_usb_buffer_count = 0;
	debug_usb_buffer_w_index = 0;
	debug_usb_buffer_r_index = 0;
	debug_usb_access_count = 0;
	debug_lcd_buffer_count = 0;
	debug_max_usb_bytecount = 0;
}

void debug_inc_usb_buffer_count(void)
{
	debug_usb_buffer_count++;
}

size_t debug_get_usb_buffer_count(void)
{
	return debug_usb_buffer_count;
}

void debug_set_usb_buffer_w_index(size_t w_index)
{
	debug_usb_buffer_w_index = w_index;
}

size_t debug_get_usb_buffer_w_index(void)
{
	return debug_usb_buffer_w_index;
}

void debug_set_usb_buffer_r_index(size_t r_index)
{
	debug_usb_buffer_r_index = r_index;
}

size_t debug_get_usb_buffer_r_index(void)
{
	return debug_usb_buffer_r_index;
}

void debug_inc_usb_access(size_t count)
{
	debug_usb_access_count += count;
}

size_t debug_get_usb_access(void)
{
	return debug_usb_access_count;
}

void debug_inc_lcd_buffer(void)
{
	debug_lcd_buffer_count++;
}

size_t debug_get_lcd_buffer(void)
{
	return debug_lcd_buffer_count;
}

void debug_set_usb_max_bytecount(size_t count)
{
	if(count > debug_max_usb_bytecount)
	{
		debug_max_usb_bytecount = count;
	}
}

size_t debug_get_usb_max_bytecount(void)
{
	return debug_max_usb_bytecount;
}
