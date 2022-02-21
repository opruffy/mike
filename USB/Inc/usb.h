/*
 * usb.h
 *
 *  Created on: Nov 30, 2020
 *      Author: Patrick
 */

#ifndef INC_USB_H_
#define INC_USB_H_

void usb_statemachine(void);
uint8_t usb_ready(void);
void usb_update(void);
void usb_stop(void);

#endif /* INC_USB_H_ */
