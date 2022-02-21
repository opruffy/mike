/*
 * calc.c
 *
 *  Created on: 18.03.2020
 *      Author: Patrick
 */

#include <stdint.h>


float calc_temp(uint16_t voltage)
{
	float value = ((float)150 * voltage / 4095) + 20;
	return value;
}

float calc_room_temp(uint16_t voltage)
{
	float value = ((float)3300 * voltage / 4095 - 509) / 6.45;
	return value;
}
