/*
 * calc.h
 *
 *  Created on: 18.03.2020
 *      Author: Patrick
 */

#ifndef INC_CALC_H_
#define INC_CALC_H_

#include <stdint.h>

float calc_temp(uint16_t voltage);
float calc_room_temp(uint16_t voltage);

#endif /* INC_CALC_H_ */
