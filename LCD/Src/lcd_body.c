/*
 * lcd_body.c
 *
 *  Created on: 15.03.2020
 *      Author: Patrick
 */

#include "lcd_matrix.h"
#include "lcd_pixel_settings.h"


uint8_t lcd_body_reset(void)
{
	lcd_matrix_reset(BODY_HOME_X, BODY_HOME_Y, BODY_LENGTH_X, BODY_LENGTH_Y);

	return 0;
}

uint8_t lcd_body_sub_reset(void)
{
	lcd_matrix_reset(BODY_SUB_HOME_X, BODY_SUB_HOME_Y, BODY_SUB_LENGTH_X, BODY_SUB_LENGTH_Y);

	return 0;
}
