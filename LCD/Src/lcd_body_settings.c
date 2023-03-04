/*
 * lcd_body_settings.c
 *
 *  Created on: 16.03.2020
 *      Author: Patrick
 */

#include <stdint.h>

#include "measure.h"
#include "measure_period.h"

#include "lcd_display_view.h"
#include "lcd_matrix.h"
#include "lcd_menu_coord.h"
#include "lcd_symbol.h"

#define MEASURE_START_STRING				("MEASURE START ")
#define MEASURE_PAUSE_STRING				("MEASURE PAUSE ")
#define MEASURE_STOP_STRING					("MEASURE STOP  ")
#define MEASURE_PERIOD_STRING				("MEASURE PERIOD")
#define SETT_FLIP_TEXT						("DISPLAY FLIP  ")

uint8_t lcd_period_mode_index = 0;
uint8_t settings_changed = 0;


static void settings_start_draw(void)
{
	lcd_symbol_rect(SETT_START_RECT_START_X, SETT_START_RECT_START_Y, SETT_START_RECT_LENGTH_X, SETT_START_RECT_LENGTH_Y);
	lcd_symbol_string(SETT_START_TEXT_START_X, SETT_START_TEXT_START_Y, MEASURE_START_STRING);
}

static void settings_start_draw_inv(void)
{
	lcd_symbol_rect_filled(SETT_START_RECT_START_X, SETT_START_RECT_START_Y, SETT_START_RECT_LENGTH_X, SETT_START_RECT_LENGTH_Y);
	lcd_symbol_string_inv(SETT_START_TEXT_START_X, SETT_START_TEXT_START_Y, MEASURE_START_STRING);
}

static void settings_pause_draw(void)
{
	lcd_symbol_rect(SETT_PAUSE_RECT_START_X, SETT_PAUSE_RECT_START_Y, SETT_PAUSE_RECT_LENGTH_X, SETT_PAUSE_RECT_LENGTH_Y);
	lcd_symbol_string(SETT_PAUSE_TEXT_START_X, SETT_PAUSE_TEXT_START_Y, MEASURE_PAUSE_STRING);
}

static void settings_pause_draw_inv(void)
{
	lcd_symbol_rect_filled(SETT_PAUSE_RECT_START_X, SETT_PAUSE_RECT_START_Y, SETT_PAUSE_RECT_LENGTH_X, SETT_PAUSE_RECT_LENGTH_Y);
	lcd_symbol_string_inv(SETT_PAUSE_TEXT_START_X, SETT_PAUSE_TEXT_START_Y, MEASURE_PAUSE_STRING);
}

static void settings_stop_draw(void)
{
	lcd_symbol_rect(SETT_STOP_RECT_START_X, SETT_STOP_RECT_START_Y, SETT_STOP_RECT_LENGTH_X, SETT_STOP_RECT_LENGTH_Y);
	lcd_symbol_string(SETT_STOP_TEXT_START_X, SETT_STOP_TEXT_START_Y, MEASURE_STOP_STRING);
}

static void settings_stop_draw_inv(void)
{
	lcd_symbol_rect_filled(SETT_STOP_RECT_START_X, SETT_STOP_RECT_START_Y, SETT_STOP_RECT_LENGTH_X, SETT_STOP_RECT_LENGTH_Y);
	lcd_symbol_string_inv(SETT_STOP_TEXT_START_X, SETT_STOP_TEXT_START_Y, MEASURE_STOP_STRING);
}

static void settings_period_draw(void)
{
	lcd_symbol_rect(SETT_PERIOD_RECT_START_X, SETT_PERIOD_RECT_START_Y, SETT_PERIOD_RECT_LENGTH_X, SETT_PERIOD_RECT_LENGTH_Y);
	lcd_symbol_string(SETT_PERIOD_TEXT_START_X, SETT_PERIOD_TEXT_START_Y, MEASURE_PERIOD_STRING);
}

static void settings_period_draw_inv(void)
{
	lcd_symbol_rect_filled(SETT_PERIOD_RECT_START_X, SETT_PERIOD_RECT_START_Y, SETT_PERIOD_RECT_LENGTH_X, SETT_PERIOD_RECT_LENGTH_Y);
	lcd_symbol_string_inv(SETT_PERIOD_TEXT_START_X, SETT_PERIOD_TEXT_START_Y, MEASURE_PERIOD_STRING);
}

static void settings_flip_draw(void)
{
	lcd_symbol_rect(SETT_FLIP_RECT_START_X, SETT_FLIP_RECT_START_Y, SETT_FLIP_RECT_LENGTH_X, SETT_FLIP_RECT_LENGTH_Y);
	lcd_symbol_string(SETT_FLIP_TEXT_START_X, SETT_FLIP_TEXT_START_Y, SETT_FLIP_TEXT);
}

static void settings_flip_draw_inv(void)
{
	lcd_symbol_rect_filled(SETT_FLIP_RECT_START_X, SETT_FLIP_RECT_START_Y, SETT_FLIP_RECT_LENGTH_X, SETT_FLIP_RECT_LENGTH_Y);
	lcd_symbol_string_inv(SETT_FLIP_TEXT_START_X, SETT_FLIP_TEXT_START_Y, SETT_FLIP_TEXT);
}


static void settings_draw_basic(void)
{
	settings_start_draw();
	settings_pause_draw();
	settings_stop_draw();
	settings_period_draw();
	settings_flip_draw();
}

// SETTINGS START
uint8_t lcd_body_settings_start_trigger_ok(void)
{
	measure_set_mode_start();

	return 0;
}

static uint8_t settings_start_button_draw(void)
{
	if(!measure_get_mode_running())
	{
		lcd_symbol_rect_filled(SETT_START_LEFT_START_X, SETT_START_LEFT_START_Y, SETT_START_LEFT_LENGTH_X, SETT_START_LEFT_LENGTH_Y);
		lcd_symbol_rect_clear(SETT_START_RIGHT_START_X, SETT_START_RIGHT_START_Y, SETT_START_RIGHT_LENGTH_X, SETT_START_RIGHT_LENGTH_Y);
		lcd_symbol_rect(SETT_START_RIGHT_START_X, SETT_START_RIGHT_START_Y, SETT_START_RIGHT_LENGTH_X, SETT_START_RIGHT_LENGTH_Y);
		lcd_symbol_string(SETT_START_RIGHT_START_X + LINE_WIDTH, SETT_START_RIGHT_START_Y + LINE_WIDTH + SPACE, "GO");
	}
	else
	{
		lcd_symbol_rect(SETT_START_LEFT_START_X, SETT_START_LEFT_START_Y, SETT_START_LEFT_LENGTH_X, SETT_START_LEFT_LENGTH_Y);
		lcd_symbol_rect_filled(SETT_START_RIGHT_START_X, SETT_START_RIGHT_START_Y, SETT_START_RIGHT_LENGTH_X, SETT_START_RIGHT_LENGTH_Y);
	}

	return 0;
}

uint8_t lcd_body_settings_start_draw(void)
{
	settings_draw_basic();
	settings_start_draw_inv();

	settings_start_button_draw();

	return 0;
}

uint8_t lcd_body_settings_start_update(void)
{
	settings_start_button_draw();

	return 0;
}

// SETTINGS PAUSE
uint8_t lcd_body_settings_pause_trigger_ok(void)
{
	measure_set_mode_pause();
	settings_changed = 1;

	return 0;
}

static uint8_t settings_pause_button_draw(void)
{
	if(!measure_get_mode_pause())
	{
		lcd_symbol_rect_filled(SETT_START_LEFT_START_X, SETT_START_LEFT_START_Y, SETT_START_LEFT_LENGTH_X, SETT_START_LEFT_LENGTH_Y);
		lcd_symbol_rect_clear(SETT_START_RIGHT_START_X, SETT_START_RIGHT_START_Y, SETT_START_RIGHT_LENGTH_X, SETT_START_RIGHT_LENGTH_Y);
		lcd_symbol_rect(SETT_START_RIGHT_START_X, SETT_START_RIGHT_START_Y, SETT_START_RIGHT_LENGTH_X, SETT_START_RIGHT_LENGTH_Y);
		lcd_symbol_string(SETT_START_RIGHT_START_X + LINE_WIDTH, SETT_START_RIGHT_START_Y + LINE_WIDTH + SPACE, "PA");
	}
	else
	{
		lcd_symbol_rect(SETT_START_LEFT_START_X, SETT_START_LEFT_START_Y, SETT_START_LEFT_LENGTH_X, SETT_START_LEFT_LENGTH_Y);
		lcd_symbol_rect_filled(SETT_START_RIGHT_START_X, SETT_START_RIGHT_START_Y, SETT_START_RIGHT_LENGTH_X, SETT_START_RIGHT_LENGTH_Y);
	}

	return 0;
}

uint8_t lcd_body_settings_pause_draw(void)
{
	settings_draw_basic();
	settings_pause_draw_inv();

	settings_pause_button_draw();

	return 0;
}

uint8_t lcd_body_settings_pause_update(void)
{
	if(settings_changed)
	{
		settings_pause_button_draw();
		settings_changed = 0;

		return 0;
	}

	return 1;
}

// SETTINGS STOP
uint8_t lcd_body_settings_stop_trigger_ok(void)
{
	measure_set_mode_stop();
	settings_changed = 1;

	return 0;
}

static uint8_t settings_stop_button_draw(void)
{
	if(!measure_get_mode_stop())
	{
		lcd_symbol_rect_filled(SETT_START_LEFT_START_X, SETT_START_LEFT_START_Y, SETT_START_LEFT_LENGTH_X, SETT_START_LEFT_LENGTH_Y);
		lcd_symbol_rect_clear(SETT_START_RIGHT_START_X, SETT_START_RIGHT_START_Y, SETT_START_RIGHT_LENGTH_X, SETT_START_RIGHT_LENGTH_Y);
		lcd_symbol_rect(SETT_START_RIGHT_START_X, SETT_START_RIGHT_START_Y, SETT_START_RIGHT_LENGTH_X, SETT_START_RIGHT_LENGTH_Y);
		lcd_symbol_string(SETT_START_RIGHT_START_X + LINE_WIDTH, SETT_START_RIGHT_START_Y + LINE_WIDTH + SPACE, "ST");
	}
	else
	{
		lcd_symbol_rect(SETT_START_LEFT_START_X, SETT_START_LEFT_START_Y, SETT_START_LEFT_LENGTH_X, SETT_START_LEFT_LENGTH_Y);
		lcd_symbol_rect_filled(SETT_START_RIGHT_START_X, SETT_START_RIGHT_START_Y, SETT_START_RIGHT_LENGTH_X, SETT_START_RIGHT_LENGTH_Y);
	}

	return 0;
}

uint8_t lcd_body_settings_stop_draw(void)
{
	settings_draw_basic();
	settings_stop_draw_inv();

	settings_stop_button_draw();

	return 0;
}

uint8_t lcd_body_settings_stop_update(void)
{
	if(settings_changed)
	{
		settings_stop_button_draw();
		settings_changed = 0;

		return 0;
	}

	return 1;
}

static uint8_t settings_period_button(uint8_t _index)
{
	if(_index != measure_period_get_current_mode())
	{
		lcd_symbol_rect_clear(SETT_PERIOD_BUTTON_START_X, SETT_PERIOD_BUTTON_START_Y, SETT_PERIOD_BUTTON_LENGTH_X, SETT_PERIOD_BUTTON_LENGTH_Y);
		lcd_symbol_rect(SETT_PERIOD_BUTTON_START_X, SETT_PERIOD_BUTTON_START_Y, SETT_PERIOD_BUTTON_LENGTH_X, SETT_PERIOD_BUTTON_LENGTH_Y);
		lcd_symbol_string(SETT_PERIOD_BUTTON_START_X + LINE_WIDTH, SETT_PERIOD_BUTTON_START_Y + LINE_WIDTH + SPACE, measure_period_get_text(_index));
	}
	else
	{
		lcd_symbol_rect_filled(SETT_PERIOD_BUTTON_START_X, SETT_PERIOD_BUTTON_START_Y, SETT_PERIOD_BUTTON_LENGTH_X, SETT_PERIOD_BUTTON_LENGTH_Y);
		lcd_symbol_string_inv(SETT_PERIOD_BUTTON_START_X + LINE_WIDTH, SETT_PERIOD_BUTTON_START_Y + LINE_WIDTH + SPACE, measure_period_get_text(_index));
	}

	lcd_symbol_symb(SETT_PERIOD_BUTTON_START_X - LETTER_X, SETT_PERIOD_BUTTON_START_Y + LINE_WIDTH + SPACE, SYM_ARROW_LEFT);
	lcd_symbol_symb(SETT_PERIOD_BUTTON_START_X + SETT_PERIOD_BUTTON_LENGTH_X, SETT_PERIOD_BUTTON_START_Y + LINE_WIDTH + SPACE, SYM_ARROW_RIGHT);

	return 0;
}

static uint8_t settings_period_button_draw(void)
{
	lcd_period_mode_index = measure_period_get_current_mode();

	return 0;
}

uint8_t lcd_body_settings_period_trigger_left(void)
{
	lcd_period_mode_index = measure_period_get_previous_mode(lcd_period_mode_index);
	settings_changed = 1;

	return 0;
}

uint8_t lcd_body_settings_period_trigger_right(void)
{
	lcd_period_mode_index = measure_period_get_next_mode(lcd_period_mode_index);
	settings_changed = 1;

	return 0;
}

uint8_t lcd_body_settings_period_trigger_ok(void)
{
	measure_period_set_mode(lcd_period_mode_index);
	settings_changed = 1;

	return 0;
}

uint8_t lcd_body_settings_period_draw(void)
{
	settings_draw_basic();
	settings_period_draw_inv();

	settings_period_button_draw();
	settings_period_button(lcd_period_mode_index);

	return 0;
}

uint8_t lcd_body_settings_period_update(void)
{
	if(settings_changed)
	{
		settings_period_button(lcd_period_mode_index);
		settings_changed = 0;

		return 0;
	}

	return 1;
}

// SETTINGS FLIP

uint8_t lcd_body_settings_flip_trigger_ok(void)
{
	if(lcd_display_view_is_original())
	{
		lcd_display_view_set_flip();
	}
	else
	{
		lcd_display_view_reset_flip();
	}
	settings_changed = 1;

	return 0;
}

static uint8_t lcd_body_settings_flip_button_draw(void)
{
	if(lcd_display_view_is_original())
	{
		lcd_symbol_rect(SETT_FLIP_LEFT_START_X, SETT_FLIP_LEFT_START_Y, SETT_FLIP_LEFT_LENGTH_X, SETT_FLIP_LEFT_LENGTH_Y);
		lcd_symbol_rect_filled(SETT_FLIP_RIGHT_START_X, SETT_FLIP_RIGHT_START_Y, SETT_FLIP_RIGHT_LENGTH_X, SETT_FLIP_RIGHT_LENGTH_Y);
	}
	else
	{
		lcd_symbol_rect_filled(SETT_FLIP_LEFT_START_X, SETT_FLIP_LEFT_START_Y, SETT_FLIP_LEFT_LENGTH_X, SETT_FLIP_LEFT_LENGTH_Y);
		lcd_symbol_rect(SETT_FLIP_RIGHT_START_X, SETT_FLIP_RIGHT_START_Y, SETT_FLIP_RIGHT_LENGTH_X, SETT_FLIP_RIGHT_LENGTH_Y);
		lcd_symbol_string(SETT_FLIP_RIGHT_START_X + LINE_WIDTH, SETT_FLIP_RIGHT_START_Y + LINE_WIDTH + SPACE, "FLIP");
	}
	return 0;
}

uint8_t lcd_body_settings_flip_draw(void)
{
	settings_draw_basic();
	settings_flip_draw_inv();

	lcd_body_settings_flip_button_draw();

	return 0;
}


uint8_t lcd_body_settings_flip_update(void)
{
	if(settings_changed)
	{
		settings_draw_basic();
		settings_flip_draw_inv();

		lcd_body_settings_flip_button_draw();

		measure_mode_status_set_changed();

		settings_changed = 0;

		return 0;
	}

	return 1;
}
