/*
 * lcd_head.c
 *
 *  Created on: 18.03.2020
 *      Author: Patrick
 */

#include "lcd_body_graph.h"
#include "lcd_body_settings.h"
#include "lcd_body_value.h"
#include "lcd_matrix.h"
#include "lcd_menu_coord.h"
#include "lcd_symbol.h"


static void draw_value(void)
{
	lcd_symbol_rect(VALUE_RECT_OUTER_START_X, VALUE_RECT_OUTER_START_Y, VALUE_RECT_OUTER_LENGTH_X, VALUE_RECT_OUTER_LENGTH_Y);
	lcd_symbol_string(VALUE_NAME_AXIS_X, VALUE_NAME_AXIS_Y, "VALUE");
}

static void draw_value_inv(void)
{
	lcd_symbol_rect_filled(VALUE_RECT_OUTER_START_X, VALUE_RECT_OUTER_START_Y, VALUE_RECT_OUTER_LENGTH_X, VALUE_RECT_OUTER_LENGTH_Y);
	lcd_symbol_string_inv(VALUE_NAME_AXIS_X, VALUE_NAME_AXIS_Y, "VALUE");
}

static void draw_graph(void)
{
	lcd_symbol_rect(GRAPH_RECT_OUTER_AXIS_X, GRAPH_RECT_OUTER_AXIS_Y, GRAPH_RECT_OUTER_LENGTH_X, GRAPH_RECT_OUTER_LENGTH_Y);
	lcd_symbol_string(GRAPH_NAME_AXIS_X, GRAPH_NAME_AXIS_Y, "GRAPH");
}

static void draw_graph_inv(void)
{
	lcd_symbol_rect_filled(GRAPH_RECT_OUTER_AXIS_X, GRAPH_RECT_OUTER_AXIS_Y, GRAPH_RECT_OUTER_LENGTH_X, GRAPH_RECT_OUTER_LENGTH_Y);
	lcd_symbol_string_inv(GRAPH_NAME_AXIS_X, GRAPH_NAME_AXIS_Y, "GRAPH");
}

static void draw_settings(void)
{
	lcd_symbol_rect(SETTINGS_RECT_OUTER_AXIS_X, SETTINGS_RECT_OUTER_AXIS_Y, SETTINGS_RECT_OUTER_LENGTH_X, SETTINGS_RECT_OUTER_LENGTH_Y);
	lcd_symbol_string(SETTINGS_NAME_AXIS_X, SETTINGS_NAME_AXIS_Y, "SETTINGS");
}

static void draw_settings_inv(void)
{
	lcd_symbol_rect_filled(SETTINGS_RECT_OUTER_AXIS_X, SETTINGS_RECT_OUTER_AXIS_Y, SETTINGS_RECT_OUTER_LENGTH_X, SETTINGS_RECT_OUTER_LENGTH_Y);
	lcd_symbol_string_inv(SETTINGS_NAME_AXIS_X, SETTINGS_NAME_AXIS_Y, "SETTINGS");
}

static void draw_debug(void)
{
	lcd_symbol_rect(DEBUG_RECT_OUTER_AXIS_X, DEBUG_RECT_OUTER_AXIS_Y, DEBUG_RECT_OUTER_LENGTH_X, DEBUG_RECT_OUTER_LENGTH_Y);
	lcd_symbol_string(DEBUG_NAME_AXIS_X, DEBUG_NAME_AXIS_Y, "DEBUG");
}

static void draw_debug_inv(void)
{
	lcd_symbol_rect_filled(DEBUG_RECT_OUTER_AXIS_X, DEBUG_RECT_OUTER_AXIS_Y, DEBUG_RECT_OUTER_LENGTH_X, DEBUG_RECT_OUTER_LENGTH_Y);
	lcd_symbol_string_inv(DEBUG_NAME_AXIS_X, DEBUG_NAME_AXIS_Y, "DEBUG");
}

// DRAW
static void draw_head_basic(void)
{
	draw_value();
	draw_graph();
	draw_settings();
	draw_debug();
}

uint8_t lcd_head_draw_value(void)
{
	draw_head_basic();
	draw_value_inv();

	return 0;
}

uint8_t lcd_head_draw_graph(void)
{
	draw_head_basic();
	draw_graph_inv();

	return 0;
}

uint8_t lcd_head_draw_settings(void)
{
	draw_head_basic();
	draw_settings_inv();

	return 0;
}

uint8_t lcd_head_draw_debug(void)
{
	draw_head_basic();
	draw_debug_inv();

	return 0;
}

// RESET
uint8_t lcd_head_reset(void)
{
	lcd_matrix_reset(MENU_HOME_X, MENU_HOME_Y, DEBUG_RECT_OUTER_AXIS_X + DEBUG_RECT_OUTER_LENGTH_X, MENU_LENGTH_Y);		// TODO reset where really need
	lcd_matrix_reset(BODY_HOME_X, BODY_HOME_Y, BODY_LENGTH_X, BODY_LENGTH_Y);

	return 0;
}
