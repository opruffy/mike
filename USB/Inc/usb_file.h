/*
 * usb_file.h
 *
 *  Created on: 01.12.2020
 *      Author: Patrick
 */

#ifndef INC_USB_FILE_H_
#define INC_USB_FILE_H_

#include <stdint.h>

uint8_t usb_mount(void);
uint8_t usb_unmount(void);
uint8_t usb_file_create(void);
uint8_t usb_file_exists_get(void);
void usb_file_exists_reset(void);
char* usb_file_get_filename(void);
uint8_t usb_file_write_data(void);

#endif /* INC_USB_FILE_H_ */
