/*
 * lcd.c
 *
 *  Created on: 08.02.2020
 *      Author: Patrick
 */

#include "clock.h"
#include "measure.h"
#include "usb.h"
#include "usb_file.h"

#include "lcd_function.h"
#include "lcd_matrix.h"
#include "lcd_menu.h"
#include "lcd_time.h"

#include "lcd_pixel_settings.h"
#include "lcd_symbol.h"


static void lcd_status_draw(void)
{
	if(!usb_ready())
	{
		lcd_symbol_symb(HEAD_USB_X, HEAD_USB_Y, SYM_USB);
	}
	else
	{
		lcd_symbol_symb_clear(HEAD_USB_X, HEAD_USB_Y);
	}
	lcd_matrix_update(HEAD_USB_X, HEAD_USB_Y, HEAD_USB_LENGTH_X, HEAD_USB_LENGTH_Y);

	if(!measure_get_mode_running())
	{
		lcd_symbol_symb(HEAD_MEASURE_MODE_X, HEAD_MEASURE_MODE_Y, SYM_PLAY);
		lcd_matrix_update(HEAD_MEASURE_MODE_X, HEAD_MEASURE_MODE_Y, HEAD_MEASURE_MODE_LENGTH_X, HEAD_MEASURE_MODE_LENGTH_Y);
	}
	else if(!measure_get_mode_pause())
	{
		lcd_symbol_symb(HEAD_MEASURE_MODE_X, HEAD_MEASURE_MODE_Y, SYM_PAUSE);
		lcd_matrix_update(HEAD_MEASURE_MODE_X, HEAD_MEASURE_MODE_Y, HEAD_MEASURE_MODE_LENGTH_X, HEAD_MEASURE_MODE_LENGTH_Y);
	}
	else if(!measure_get_mode_stop())
	{
		lcd_symbol_symb(HEAD_MEASURE_MODE_X, HEAD_MEASURE_MODE_Y, SYM_STOP);
		lcd_matrix_update(HEAD_MEASURE_MODE_X, HEAD_MEASURE_MODE_Y, HEAD_MEASURE_MODE_LENGTH_X, HEAD_MEASURE_MODE_LENGTH_Y);
	}

	lcd_time_draw();
}

static void lcd_status_update(void)
{
	if(!usb_ready())
	{
		lcd_symbol_symb(HEAD_USB_X, HEAD_USB_Y, SYM_USB);
	}
	else
	{
		lcd_symbol_symb_clear(HEAD_USB_X, HEAD_USB_Y);
	}
	lcd_matrix_update(HEAD_USB_X, HEAD_USB_Y, HEAD_USB_LENGTH_X, HEAD_USB_LENGTH_Y);

	if(!measure_mode_status_get_changed())
	{
		if(!measure_get_mode_running())
		{
			lcd_symbol_symb(HEAD_MEASURE_MODE_X, HEAD_MEASURE_MODE_Y, SYM_PLAY);
			lcd_matrix_update(HEAD_MEASURE_MODE_X, HEAD_MEASURE_MODE_Y, HEAD_MEASURE_MODE_LENGTH_X, HEAD_MEASURE_MODE_LENGTH_Y);
		 	measure_mode_status_update();
		}
		else if(!measure_get_mode_pause())
		{
			lcd_symbol_symb(HEAD_MEASURE_MODE_X, HEAD_MEASURE_MODE_Y, SYM_PAUSE);
			lcd_matrix_update(HEAD_MEASURE_MODE_X, HEAD_MEASURE_MODE_Y, HEAD_MEASURE_MODE_LENGTH_X, HEAD_MEASURE_MODE_LENGTH_Y);
		}
		else if(!measure_get_mode_stop())
		{
			lcd_symbol_symb(HEAD_MEASURE_MODE_X, HEAD_MEASURE_MODE_Y, SYM_STOP);
			lcd_matrix_update(HEAD_MEASURE_MODE_X, HEAD_MEASURE_MODE_Y, HEAD_MEASURE_MODE_LENGTH_X, HEAD_MEASURE_MODE_LENGTH_Y);
		}
	}

	if(!clock_get_status())
	{
		lcd_time_update();
		clock_reset_status();
	}
}

uint8_t lcd_draw(void)
{
	lcd_initialize();

	lcd_menu_draw();
	lcd_status_draw();

	return 0;
}

uint8_t lcd_update(void)
{
	lcd_menu_update();
	lcd_status_update();

	return 0;
}

void lcd_stop(void)
{
	lcd_menu_stop();
}
