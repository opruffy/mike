/*
 * lcd_pixel_settings.h
 *
 *  Created on: 15.03.2020
 *      Author: Patrick
 */

#ifndef LCD_PIXEL_SETTINGS_H_
#define LCD_PIXEL_SETTINGS_H_

#include "lcd_config.h"

#define SPACE					(1)
#define LINE_WIDTH				(1)

// LETTER
#define LETTER_X				(6)
#define LETTER_Y				(8)

// MENU
#define MENU_HOME_X				(0)
#define MENU_HOME_Y				(0)
#define MENU_LENGTH_X			(30 * 8)
#define MENU_LENGTH_Y			(2 * 8)

// SYMBOL
#define SYMBOL_HOME_X			(MENU_HOME_X + MENU_LENGTH_X)
#define SYMBOL_HOME_Y			(0)
#define SYMBOL_LENGTH_X			(10 * 8)
#define SYMBOL_LENGTH_Y			(2 * 8)

// BODY
#define BODY_HOME_X				(0)
#define BODY_HOME_Y				(MENU_HOME_Y + MENU_LENGTH_Y)
#define BODY_LENGTH_X			(30 * 8)
#define BODY_LENGTH_Y			(14 * 8)

// SUB BODY
#define BODY_SUB_HOME_X				(15 * 8)
#define BODY_SUB_HOME_Y				(MENU_HOME_Y + MENU_LENGTH_Y)
#define BODY_SUB_LENGTH_X			(10 * 8)
#define BODY_SUB_LENGTH_Y			(14 * 8)

// GRAPH
#define ORIGIN_SKALE			(3)
#define OPTICAL_SPACE			(3)

// - ARROW
#define ARROW_LENGTH_X				(5)
#define ARROW_LENGTH_Y				(5)

// - X-AXIS
#define X_AXIS_ORIGIN_X				(SPACE + 3 * LETTER_X + OPTICAL_SPACE + ORIGIN_SKALE + LINE_WIDTH)				// <-- Start in x
#define X_AXIS_ORIGIN_Y				((NUMBER_OF_LINES) - (LETTER_Y + OPTICAL_SPACE + ORIGIN_SKALE + LINE_WIDTH))	// <-- Start in y

#define X_AXIS_START_X				(X_AXIS_ORIGIN_X - OPTICAL_SPACE - LINE_WIDTH)
#define X_AXIS_START_Y				(X_AXIS_ORIGIN_Y)

#define X_AXIS_INC_X				(X_AXIS_ORIGIN_X - 1)
#define X_AXIS_INC_Y				(X_AXIS_ORIGIN_Y + 1)

#define X_AXIS_LENGTH_X				(120)

#define X_AXIS_ARROW_START_X		(X_AXIS_ORIGIN_X + X_AXIS_LENGTH_X)
#define X_AXIS_ARROW_START_Y		(X_AXIS_ORIGIN_Y - (ARROW_LENGTH_Y / 2))

#define X_AXIS_NAME_X				(X_AXIS_ARROW_START_X - 1 + ARROW_LENGTH_X + SPACE + 1)		// -1 .. starting point correction, +1 .. letter correction
#define X_AXIS_NAME_Y				(X_AXIS_START_Y - (LETTER_Y / 2 - 1))

// - Y-AXIS
#define Y_AXIS_ORIGIN_X				(X_AXIS_ORIGIN_X - LINE_WIDTH)
#define Y_AXIS_ORIGIN_Y				(X_AXIS_ORIGIN_Y - LINE_WIDTH)

#define Y_AXIS_START_X				(Y_AXIS_ORIGIN_X)
#define Y_AXIS_START_Y				(Y_AXIS_ORIGIN_Y + OPTICAL_SPACE + LINE_WIDTH)

#define Y_AXIS_INC_X				(Y_AXIS_ORIGIN_X - 1)
#define Y_AXIS_INC_Y				(Y_AXIS_ORIGIN_Y + 1)

#define Y_AXIS_LENGTH_Y				(81)

#define Y_AXIS_ARROW_START_X		(Y_AXIS_ORIGIN_X - (ARROW_LENGTH_X / 2))
#define Y_AXIS_ARROW_START_Y		(Y_AXIS_ORIGIN_Y + 1 - (Y_AXIS_LENGTH_Y + ARROW_LENGTH_Y))	// +1 ..  starting point correction

#define Y_AXIS_NAME_X				(Y_AXIS_START_X - LETTER_X)
#define Y_AXIS_NAME_Y				(Y_AXIS_ARROW_START_Y - (LETTER_Y + SPACE))

// GRAPH - MENU AXIS
#define GRAPH_MENU_AXIS_UP_START_X		(PIXELS_PER_LINE - (ARROW_LENGTH_X))
#define GRAPH_MENU_AXIS_UP_START_Y		(Y_AXIS_ARROW_START_Y)

#define GRAPH_MENU_CUBE_LENGTH			(3 * LINE_WIDTH)
#define GRAPH_MENU_CUBE_GAB				(6 * SPACE + GRAPH_MENU_CUBE_LENGTH)
#define GRAPH_MENU_AXIS_LENGTH			(4 * GRAPH_MENU_CUBE_GAB - 6 * SPACE)

#define GRAPH_MENU_AXIS_START_X			(GRAPH_MENU_AXIS_UP_START_X + (ARROW_LENGTH_X / 2))
#define GRAPH_MENU_AXIS_START_Y			(GRAPH_MENU_AXIS_UP_START_Y + ARROW_LENGTH_Y)

#define GRAPH_MENU_AXIS_DOWN_START_X	(GRAPH_MENU_AXIS_UP_START_X)
#define GRAPH_MENU_AXIS_DOWN_START_Y	(GRAPH_MENU_AXIS_START_Y + GRAPH_MENU_AXIS_LENGTH)

#define GRAPH_MENU_NUMBER_START_X		(PIXELS_PER_LINE - 8 * LETTER_X)
#define GRAPH_MENU_NUMBER_START_Y		(BODY_SUB_HOME_Y)

#define GRAPH_MENU_ADC_ORDER_START_X	(PIXELS_PER_LINE - 8 * LETTER_X)
#define GRAPH_MENU_ADC_ORDER_START_Y	(BODY_SUB_HOME_Y + LETTER_Y)

// HEAD
// - TIME
#define HEAD_TIME_X						(PIXELS_PER_LINE - 10 * LETTER_X)
#define HEAD_TIME_Y						(2 * SPACE)

#define HEAD_TIME_LENGTH_X				(10 * LETTER_X)
#define HEAD_TIME_LENGTH_Y				(SPACE + LETTER_Y)

// - MEASURE MODE
#define HEAD_MEASURE_MODE_X				(HEAD_TIME_X - LETTER_X - 2 * SPACE)
#define HEAD_MEASURE_MODE_Y				(HEAD_TIME_Y)

#define HEAD_MEASURE_MODE_LENGTH_X		(LETTER_X)
#define HEAD_MEASURE_MODE_LENGTH_Y		(LETTER_Y)

// - USB
#define HEAD_USB_X						(HEAD_MEASURE_MODE_X - LETTER_X - 2 * SPACE)
#define HEAD_USB_Y						(HEAD_TIME_Y)

#define HEAD_USB_LENGTH_X				(LETTER_X)
#define HEAD_USB_LENGTH_Y				(LETTER_Y)

// SYMBOL INDEX
#define SYMBOL_PUNKT						(0)
#define SYMBOL_DOPPELPUNKT					(1)
#define SYM_SQUARE_BRACKETS_LEFT			(2)
#define SYM_SQUARE_BRACKETS_RIGHT			(3)
#define SYM_DEGREE							(4)
#define SYM_PLAY							(5)
#define SYM_PAUSE							(6)
#define SYM_STOP							(7)
#define SYM_USB								(8)
#define SYM_HYPHEN							(9)
#define SYM_ARROW_RIGHT						(10)
#define SYM_ARROW_LEFT						(11)

// MENU INDEX
typedef enum
{
	// main menu
	menu_value = 0,
	menu_graph,
	menu_sett,
	menu_debug,

	// sub menus
	menu_value_body,

	menu_graph_body,

	menu_sett_start,
	menu_sett_pause,
	menu_sett_stop,
	menu_sett_period,
	menu_sett_flip,

	menu_debug_body,

	// other tasks
	menu_noaction,
}menu_task_t;

#endif /* LCD_PIXEL_SETTINGS_H_ */
