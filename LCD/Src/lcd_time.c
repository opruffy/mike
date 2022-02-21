/*
 * lcd_time.c
 *
 *  Created on: 18.03.2020
 *      Author: Patrick
 */

#include "clock.h"

#include "lcd_pixel_settings.h"
#include "lcd_matrix.h"
#include "lcd_symbol.h"


static void lcd_time_draw_time(uint8_t hour, uint8_t min, uint8_t sec, uint8_t msec)
{
	// 10 chars + 1 char for null terminated
	char tmp[11] = {0};

	tmp[0] = hour / 10 + '0';
	tmp[1] = hour % 10 + '0';
	tmp[2] = ':';

	tmp[3] = min / 10 + '0';
	tmp[4] = min % 10 + '0';
	tmp[5] = ':';

	tmp[6] = sec / 10 + '0';
	tmp[7] = sec % 10 + '0';
	tmp[8] = '.';

	tmp[9] = msec % 10 + '0';

	lcd_symbol_string(HEAD_TIME_X, HEAD_TIME_Y, tmp);
}

void lcd_time_draw(void)
{
	clock_reset();
	lcd_time_draw_time(clock_get_hour(), clock_get_min(), clock_get_sec(), clock_get_msec());
	lcd_matrix_update(HEAD_TIME_X, 0, HEAD_TIME_LENGTH_X, HEAD_TIME_LENGTH_Y);
}

void lcd_time_update(void)
{
	lcd_time_draw_time(clock_get_hour(), clock_get_min(), clock_get_sec(), clock_get_msec());
	lcd_matrix_update(HEAD_TIME_X, 0, HEAD_TIME_LENGTH_X, HEAD_TIME_LENGTH_Y);
}
