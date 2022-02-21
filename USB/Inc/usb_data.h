/*
 * usb_data.h
 *
 *  Created on: 01.12.2020
 *      Author: Patrick
 */

#ifndef INC_USB_DATA_H_
#define INC_USB_DATA_H_

void usb_data_set_data(void);
size_t usb_data_get_buffer_count(void);
size_t usb_data_get_data(char* str, size_t bytes_count);

#endif /* INC_USB_DATA_H_ */
