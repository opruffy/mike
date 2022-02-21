/*
 * buffer.h
 *
 *  Created on: 12.05.2020
 *      Author: Patrick
 */

#ifndef INC_BUFFER_H_
#define INC_BUFFER_H_

#include <stdint.h>
#include <stddef.h>

#define ADC_VALUES		13	// TODO change to generic setting

typedef struct
{
	uint16_t buffer[ADC_VALUES];
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
}buffer_info_t;

#endif /* INC_BUFFER_H_ */
