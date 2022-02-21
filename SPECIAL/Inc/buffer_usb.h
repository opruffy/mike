/*
 * buffer_usb.h
 *
 *  Created on: 01.12.2020
 *      Author: Patrick
 */

#ifndef INC_BUFFER_USB_H_
#define INC_BUFFER_USB_H_

#include "buffer.h"

uint8_t buffer_usb_set_value(uint32_t *value, size_t length);
size_t buffer_usb_get_values(buffer_info_t* buffer, size_t count);
size_t buffer_usb_get_count(void);
uint32_t buffer_usb_get_last_time(void);

void buffer_usb_reset_counter(void);

#endif /* INC_BUFFER_USB_H_ */
