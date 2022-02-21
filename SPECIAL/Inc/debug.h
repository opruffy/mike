/*
 * debug.h
 *
 *  Created on: 27.03.2021
 *      Author: Patrick
 */

#ifndef INC_DEBUG_H_
#define INC_DEBUG_H_

#include <stddef.h>

void debug_reset_counter(void);

void debug_inc_usb_buffer_count(void);
size_t debug_get_usb_buffer_count(void);
void debug_set_usb_buffer_w_index(size_t w_index);
void debug_set_usb_buffer_r_index(size_t r_index);
size_t debug_get_usb_buffer_w_index(void);
size_t debug_get_usb_buffer_r_index(void);
void debug_inc_usb_access(size_t count);
size_t debug_get_usb_access(void);
void debug_inc_lcd_buffer(void);
size_t debug_get_lcd_buffer(void);
void debug_set_usb_max_bytecount(size_t count);
size_t debug_get_usb_max_bytecount(void);

#endif /* INC_DEBUG_H_ */
