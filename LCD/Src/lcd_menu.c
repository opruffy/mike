/*
 * lcd_menu.c
 *
 *  Created on: 17.03.2020
 *      Author: Patrick
 */

#include "button.h"
#include "clock.h"
#include "measure.h"

#include "lcd_body.h"
#include "lcd_body_graph.h"
#include "lcd_body_settings.h"
#include "lcd_body_value.h"
#include "lcd_body_debug.h"
#include "lcd_display_view.h"
#include "lcd_head.h"
#include "lcd_matrix.h"
#include "lcd_pixel_settings.h"

#include "main.h"

typedef uint8_t (*draw_fp)(void);
typedef uint8_t (*reset_fp)(void);
typedef uint8_t (*trigger_fp)(void);
typedef uint8_t (*trigger_draw_fp)(void);
typedef uint8_t (*update_fp)(void);

typedef enum
{
	button_up = 0,
	button_down,
	button_left,
	button_right,
	button_ok,
}action_t;

typedef struct
{
	draw_fp draw;
	reset_fp reset_matrix;
	trigger_fp trigger[5];
	trigger_draw_fp trigger_draw;
	update_fp update;
	menu_task_t task[5];
	menu_task_t parent;
	menu_task_t child;
}menu_t;

menu_task_t menu_active = menu_graph;		// TODO change to value menu.

const menu_t menu_tree[] =
{
		// value
		{
			.draw = &lcd_head_draw_value,
			.reset_matrix = &lcd_head_reset,
			.update = NULL,
			.task =
			{
				menu_noaction,			// up
				menu_noaction,			// down
				menu_debug,				// left
				menu_graph,				// right
				menu_noaction,			// OK
			},
			.child = menu_value_body,
			.parent = menu_none,
		},
		// graph
		{
			.draw = &lcd_head_draw_graph,
			.reset_matrix = &lcd_head_reset,
			.update = NULL,
			.task =
			{
				menu_noaction,
				menu_noaction,
				menu_value,
				menu_sett,
				menu_noaction,
			},
			.child = menu_graph_body,
			.parent = menu_none,
		},
		// settings
		{
			.draw = &lcd_head_draw_settings,
			.reset_matrix = &lcd_head_reset,
			.update = NULL,
			.task =
			{
				menu_noaction,
				menu_noaction,
				menu_graph,
				menu_debug,
				menu_noaction,
			},
			.child = menu_sett_start,
			.parent = menu_none,
		},
		// debug
		{
			.draw = &lcd_head_draw_debug,
			.reset_matrix = &lcd_head_reset,
			.update = NULL,
			.task =
			{
				menu_noaction,
				menu_noaction,
				menu_sett,
				menu_value,
				menu_noaction,
			},
			.child = menu_debug_body,
			.parent = menu_none,
		},

		// value - body
		{
			.draw = &lcd_body_value_draw,
			.reset_matrix = &lcd_body_reset,
			.update = &lcd_body_value_update,
			.task =
			{
				menu_noaction,
				menu_noaction,
				menu_none,
				menu_none,
				menu_noaction,
			},
			.child = menu_none,
			.parent = menu_value,
		},

		// graph - body
		{
			.draw = &lcd_body_graph_draw,
			.reset_matrix = &lcd_body_reset,
			.trigger =
			{
				&lcd_body_graph_trigger_up,					// up
				&lcd_body_graph_trigger_down,				// down
				NULL,										// left
				NULL,										// right
				NULL,										// OK
			},
			.update = &lcd_body_graph_update,
			.task =
			{
				menu_graph_body,
				menu_graph_body,
				menu_none,
				menu_none,
				menu_noaction,
			},
			.child = menu_none,
			.parent = menu_graph,
		},

		// settings - start
		{
			.draw = &lcd_body_settings_start_draw,
			.reset_matrix = &lcd_body_reset,
			.trigger =
			{
				NULL,										// up
				NULL,										// down
				NULL,										// left
				NULL,										// right
				&lcd_body_settings_start_trigger_ok,		// OK
			},
			.update = &lcd_body_settings_start_update,
			.task =
			{
				menu_sett_flip,
				menu_sett_pause,
				menu_none,
				menu_none,
				menu_sett_start,
			},
			.child = menu_none,
			.parent = menu_sett,
		},
		// settings - pause
		{
			.draw = &lcd_body_settings_pause_draw,
			.reset_matrix = &lcd_body_reset,
			.trigger =
			{
				NULL,										// up
				NULL,										// down
				NULL,										// left
				NULL,										// right
				&lcd_body_settings_pause_trigger_ok,		// OK
			},
			.update = &lcd_body_settings_pause_update,
			.task =
			{
				menu_sett_start,
				menu_sett_stop,
				menu_none,
				menu_none,
				menu_sett_pause,
			},
			.child = menu_none,
			.parent = menu_sett,
		},
		// settings - stop
		{
			.draw = &lcd_body_settings_stop_draw,
			.reset_matrix = &lcd_body_reset,
			.trigger =
			{
				NULL,										// up
				NULL,										// down
				NULL,										// left
				NULL,										// right
				&lcd_body_settings_stop_trigger_ok,			// OK
			},
			.update = &lcd_body_settings_stop_update,
			.task =
			{
				menu_sett_pause,
				menu_sett_period,
				menu_none,
				menu_none,
				menu_sett_stop,
			},
			.child = menu_none,
			.parent = menu_sett,
		},
		// settings - period
		{
			.draw = &lcd_body_settings_period_draw,
			.reset_matrix = &lcd_body_reset,
			.trigger =
			{
				NULL,										// up
				NULL,										// down
				&lcd_body_settings_period_trigger_left,		// left
				&lcd_body_settings_period_trigger_right,	// right
				&lcd_body_settings_period_trigger_ok,		// OK
			},
			.trigger_draw = &lcd_body_settings_period_trigger_draw,
			.update = &lcd_body_settings_period_update,
			.task =
			{
				menu_sett_stop,
				menu_sett_flip,
				menu_sett_period,
				menu_sett_period,
				menu_sett_period,
			},
			.child = menu_none,
			.parent = menu_sett,
		},
		// settings - flip
		{
			.draw = lcd_body_settings_flip_draw,
			.reset_matrix = &lcd_body_reset,
			.trigger =
			{
				NULL,										// up
				NULL,										// down
				NULL,										// left
				NULL,										// right
				lcd_body_settings_flip_trigger_ok,			// OK
			},
			.update = lcd_body_settings_flip_update,
			.task =
			{
				menu_sett_period,
				menu_sett_start,
				menu_none,
				menu_none,
				menu_sett_flip,
			},
			.child = menu_none,
			.parent = menu_sett,
		},

		// debug - body
		{
			.draw = &lcd_body_debug_draw,
			.reset_matrix = &lcd_body_reset,
			.update = &lcd_body_debug_update,
			.task =
			{
				menu_noaction,
				menu_noaction,
				menu_none,
				menu_none,
				menu_noaction,
			},
			.child = menu_none,
			.parent = menu_debug,
		},
};

uint8_t triggered = 0;

static menu_task_t get_task_from_tree(menu_task_t task, action_t action)
{
	menu_task_t new_task = task;

	if(menu_tree[task].task[action] != menu_noaction)
	{
		if(menu_tree[task].task[action] != menu_none)
		{
			if(menu_tree[task].trigger[action] != NULL)
			{
				menu_tree[task].trigger[action]();
				triggered = 1;
			}

			new_task = menu_tree[task].task[action];
		}
		else
		{
			if(menu_tree[task].parent != menu_none)
			{
				new_task = get_task_from_tree(menu_tree[task].parent, action);
			}
		}
	}

	return new_task;
}

static menu_task_t get_new_task(menu_task_t task)
{
	menu_task_t new_task = task;

	if(button_get_pressed_any())
	{
		if(button_get_pressed_up())
		{
			if(lcd_display_view_is_original())
				new_task = get_task_from_tree(task, button_up);
			else
				new_task = get_task_from_tree(task, button_down);
		}
		else if(button_get_pressed_down())
		{
			if(lcd_display_view_is_original())
				new_task = get_task_from_tree(task, button_down);
			else
				new_task = get_task_from_tree(task, button_up);
		}
		else if(button_get_pressed_left())
		{
			if(lcd_display_view_is_original())
				new_task = get_task_from_tree(task, button_left);
			else
				new_task = get_task_from_tree(task, button_right);
		}
		else if(button_get_pressed_right())
		{
			if(lcd_display_view_is_original())
				new_task = get_task_from_tree(task, button_right);
			else
				new_task = get_task_from_tree(task, button_left);
		}
		else if(button_get_pressed_ok())
		{
			new_task = get_task_from_tree(task, button_ok);
		}
	}

	return new_task;
}

static menu_task_t get_child(menu_task_t task)
{
	menu_task_t new_task = task;

	if(menu_tree[task].child != menu_none)
	{
		menu_tree[menu_tree[task].child].draw();
		new_task = get_child(menu_tree[task].child);
	}

	return new_task;
}

static menu_task_t get_parent(menu_task_t task)
{
	menu_task_t new_task = task;

	if(menu_tree[task].parent != menu_none)
	{
		menu_tree[menu_tree[task].parent].reset_matrix();
		new_task = get_parent(menu_tree[task].parent);
		menu_tree[menu_tree[task].parent].draw();
	}

	return new_task;
}

void lcd_menu_update(void)
{
	menu_task_t task = get_new_task(menu_active);

	if(task != menu_none)
	{
		if(triggered == 1)
		{
			menu_tree[task].reset_matrix();
			get_parent(task);

			if(menu_tree[task].trigger_draw != NULL)	// TODO is there a better solution?
				menu_tree[task].trigger_draw();
			else
				menu_tree[task].draw();

			measure_mode_status_set_changed();
			clock_set_status();

			lcd_matrix_update(0, 0, 240, 128);

			triggered = 0;
		}
		else if(menu_active != task)
		{
			menu_tree[task].reset_matrix();
			menu_tree[task].draw();
			menu_active = get_child(task);

			lcd_matrix_update(0, 0, 240, 128);
		}
		else if(menu_tree[menu_active].update != NULL)
		{
			menu_tree[menu_active].update();

			lcd_matrix_update(0, 0, 240, 128);
		}
	}
}

void lcd_menu_draw(void)
{
	menu_tree[menu_active].draw();
	menu_active = get_child(menu_active);

	lcd_matrix_update(0, 0, 240, 128);
}

void lcd_menu_stop(void)
{
	lcd_body_graph_stop();
}
