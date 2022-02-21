/*
 * usb_data.c
 *
 *  Created on: 01.12.2020
 *      Author: Patrick
 */

#include <stdio.h>
#include <string.h>

#include "buffer_usb.h"
#include "calc.h"
#include "debug.h"

#define USB_BUF_SIZE		10


size_t usb_data_get_data(char* str, size_t count)
{
	buffer_info_t usb_buffer[USB_BUF_SIZE] = { 0 };

	if(count > USB_BUF_SIZE)
		count = USB_BUF_SIZE;

	count = buffer_usb_get_values(&usb_buffer[0], count);
	if(!count)
		return 0;

	for(size_t j = 0; j < count; j ++)
	{
		char tmp[10] = {0};

		// hour
		sprintf(tmp, "%02u:", usb_buffer[j].hour);
		strcat(str, tmp);

		// min
		sprintf(tmp, "%02u:", usb_buffer[j].min);
		strcat(str, tmp);

		// sec
		sprintf(tmp, "%02u;", usb_buffer[j].sec);
		strcat(str, tmp);

		for(uint32_t i = 0; i < ADC_VALUES; i++)
		{
			float value = calc_temp(usb_buffer[j].buffer[i]);
			sprintf(tmp, "%.2f;", value);
			strcat(str, tmp);
		}
		strcat(str, "\n");
	}

	debug_inc_usb_access(count);

	return strlen(str);
}
