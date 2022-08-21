/*
 * usb.c
 *
 *  Created on: Nov 30, 2020
 *      Author: Patrick
 */

#include "buffer_usb.h"
#include "fatfs.h"
#include "measure.h"
#include "usb_host.h"
#include "usb_data.h"
#include "usb_file.h"

extern ApplicationTypeDef Appli_state;
uint8_t usb_file_ready = 1;		// TODO optimize?

void usb_statemachine(void)
{
	switch (Appli_state)
	{
		case APPLICATION_IDLE:
			break;

		case APPLICATION_START:
			break;

		case APPLICATION_READY:
			if(!usb_mount() && !measure_get_mode_running())
			{
				// create file
				if(usb_file_exists_get())
				{
					usb_file_create();
				}
				usb_file_ready = 0;
			}
			break;

		case APPLICATION_DISCONNECT:
			usb_file_ready = 1;
			usb_file_exists_reset();
			break;

		default:
			break;
	}
}

uint8_t usb_ready(void)
{
	return usb_file_ready;
}

void usb_update(void)
{
	if(!usb_file_ready && !measure_get_mode_running() && buffer_usb_get_count())
	{
		usb_file_write_data();
	}
}

void usb_stop(void)	// TODO testen
{
	if(!measure_get_mode_stop())
	{
		if(!usb_file_ready)
		{
			if(buffer_usb_get_count())
			{
				usb_file_write_data();
			}
		}

		buffer_usb_reset_counter();

		usb_file_exists_reset();
		usb_file_ready = 1;
	}
}
