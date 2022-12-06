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
typedef uint8_t (*update_fp)(void);

typedef enum
{
	button_up = 0,
	button_down,
	button_left,
	button_right,
	button_ok,
}action_t;

typedef enum
{
	task_update = 0,		// no action and call update function
	task_change_main_menu,
	task_change_menu,
	task_update_lcd,
	task_update_submenu,
}task_t;

typedef struct
{
	task_t task[5];
	menu_task_t next_menu[5];
	menu_task_t parent;
	menu_task_t child;
	reset_fp reset_matrix;
	draw_fp draw;
	update_fp update;
	trigger_fp trigger[5];
}menu_t;

menu_task_t menu_active = menu_graph;		// TODO change to value menu.

const menu_t menu_tree[] =
{
		// value
		{
			.task =
			{
				task_update,				// up
				task_update,				// down
				task_change_main_menu,		// left
				task_change_main_menu,		// right
				task_update,				// ok
			},
			.next_menu =
			{
				menu_noaction,			// up
				menu_noaction,			// down
				menu_debug,				// left
				menu_graph,				// right
				menu_noaction,			// OK
			},
			.parent = menu_noaction,
			.child = menu_value_body,
			.reset_matrix = &lcd_head_reset,
			.draw = &lcd_head_draw_value,
		},
		// graph
		{
			.task =
			{
				task_update,				// up
				task_update,				// down
				task_change_main_menu,		// left
				task_change_main_menu,		// right
				task_update,				// ok
			},
			.next_menu =
			{
				menu_noaction,
				menu_noaction,
				menu_value,
				menu_sett,
				menu_noaction,
			},
			.parent = menu_noaction,
			.child = menu_graph_body,
			.reset_matrix = &lcd_head_reset,
			.draw = &lcd_head_draw_graph,
		},
		// settings
		{
			.task =
			{
				task_update,				// up
				task_update,				// down
				task_change_main_menu,		// left
				task_change_main_menu,		// right
				task_update,				// ok
			},
			.next_menu =
			{
				menu_noaction,
				menu_noaction,
				menu_graph,
				menu_debug,
				menu_noaction,
			},
			.parent = menu_noaction,
			.child = menu_sett_start,
			.reset_matrix = &lcd_head_reset,
			.draw = &lcd_head_draw_settings,
		},
		// debug
		{
			.task =
			{
				task_update,				// up
				task_update,				// down
				task_change_main_menu,		// left
				task_change_main_menu,		// right
				task_update,				// ok
			},
			.next_menu =
			{
				menu_noaction,
				menu_noaction,
				menu_sett,
				menu_value,
				menu_noaction,
			},
			.parent = menu_noaction,
			.child = menu_debug_body,
			.reset_matrix = &lcd_head_reset,
			.draw = &lcd_head_draw_debug,
		},

		// value - body
		{
			.task =
			{
				task_update,				// up
				task_update,				// down
				task_change_main_menu,		// left
				task_change_main_menu,		// right
				task_update,				// ok
			},
			.parent = menu_value,
			.child = menu_noaction,
			.reset_matrix = &lcd_body_reset,
			.draw = &lcd_body_value_draw,
			.update = &lcd_body_value_update,
		},

		// graph - body
		{
			.task =
			{
				task_update_submenu,		// up
				task_update_submenu,		// down
				task_change_main_menu,		// left
				task_change_main_menu,		// right
				task_update,				// ok
			},
			.parent = menu_graph,
			.child = menu_noaction,
			.reset_matrix = &lcd_body_reset,
			.draw = &lcd_body_graph_draw,
			.update = &lcd_body_graph_update,
			.trigger =
			{
				&lcd_body_graph_trigger_up,					// up
				&lcd_body_graph_trigger_down,				// down
				NULL,										// left
				NULL,										// right
				NULL,										// OK
			},
		},

		// settings - start
		{
			.task =
			{
				task_change_menu,			// up
				task_change_menu,			// down
				task_change_main_menu,		// left
				task_change_main_menu,		// right
				task_update_submenu,		// ok
			},
			.next_menu =
			{
				menu_sett_flip,
				menu_sett_pause,
				menu_noaction,
				menu_noaction,
				menu_noaction,
			},
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
			.child = menu_noaction,
			.parent = menu_sett,
		},
		// settings - pause
		{
			.task =
			{
				task_change_menu,			// up
				task_change_menu,			// down
				task_change_main_menu,		// left
				task_change_main_menu,		// right
				task_update_submenu,		// ok
			},
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
			.next_menu =
			{
				menu_sett_start,
				menu_sett_stop,
				menu_noaction,
				menu_noaction,
				menu_noaction,
			},
			.child = menu_noaction,
			.parent = menu_sett,
		},
		// settings - stop
		{
			.task =
			{
				task_change_menu,			// up
				task_change_menu,			// down
				task_change_main_menu,		// left
				task_change_main_menu,		// right
				task_update_submenu,		// ok
			},
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
			.next_menu =
			{
				menu_sett_pause,
				menu_sett_period,
				menu_noaction,
				menu_noaction,
				menu_noaction,
			},
			.child = menu_noaction,
			.parent = menu_sett,
		},
		// settings - period
		{
			.task =
			{
				task_change_menu,			// up
				task_change_menu,			// down
				task_update_submenu,		// left
				task_update_submenu,		// right
				task_update_submenu,		// ok
			},
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
			.update = &lcd_body_settings_period_update,
			.next_menu =
			{
				menu_sett_stop,
				menu_sett_flip,
				menu_noaction,
				menu_noaction,
				menu_noaction,
			},
			.child = menu_noaction,
			.parent = menu_sett,
		},
		// settings - flip
		{
			.task =
			{
				task_change_menu,			// up
				task_change_menu,			// down
				task_change_main_menu,		// left
				task_change_main_menu,		// right
				task_update_lcd,			// ok
			},
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
			.next_menu =
			{
				menu_sett_period,
				menu_sett_start,
				menu_noaction,
				menu_noaction,
				menu_noaction,
			},
			.child = menu_noaction,
			.parent = menu_sett,
		},

		// debug - body
		{
			.task =
			{
				task_update,				// up
				task_update,				// down
				task_change_main_menu,		// left
				task_change_main_menu,		// right
				task_update,				// ok
			},
			.parent = menu_debug,
			.child = menu_noaction,
			.reset_matrix = &lcd_body_reset,
			.draw = &lcd_body_debug_draw,
			.update = &lcd_body_debug_update,
		},
};

static menu_task_t get_task_from_tree(menu_task_t task, action_t action)
{
	menu_task_t new_task = task;

	switch(menu_tree[task].task[action])
	{
		case task_change_main_menu:
			if(menu_tree[task].parent != menu_noaction)
			{
				new_task = menu_tree[menu_tree[task].parent].next_menu[action];
			}
			else
			{
				new_task = menu_tree[task].next_menu[action];
			}
			break;
		case task_change_menu:
			new_task = menu_tree[task].next_menu[action];
			break;
		case task_update_lcd:
			if(menu_tree[task].trigger[action] != NULL)
			{
				menu_tree[task].trigger[action]();
			}
			menu_tree[menu_tree[task].parent].reset_matrix();
			menu_tree[menu_tree[task].parent].draw();
			break;
		case task_update_submenu:
			if(menu_tree[task].trigger[action] != NULL)
			{
				menu_tree[task].trigger[action]();
			}
			break;
		case task_update:
		default:
			break;
	}

	return new_task;
}

static menu_task_t get_child_task(menu_task_t task)
{
	menu_task_t new_task = task;

	if(menu_tree[task].child != menu_noaction)
	{
		new_task = get_child_task(menu_tree[task].child);
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
			{
				new_task = get_task_from_tree(task, button_up);
			}
			else
			{
				new_task = get_task_from_tree(task, button_down);
			}
		}
		else if(button_get_pressed_down())
		{
			if(lcd_display_view_is_original())
			{
				new_task = get_task_from_tree(task, button_down);
			}
			else
			{
				new_task = get_task_from_tree(task, button_up);
			}
		}
		else if(button_get_pressed_left())
		{
			if(lcd_display_view_is_original())
			{
				new_task = get_task_from_tree(task, button_left);
			}
			else
			{
				new_task = get_task_from_tree(task, button_right);
			}
		}
		else if(button_get_pressed_right())
		{
			if(lcd_display_view_is_original())
			{
				new_task = get_task_from_tree(task, button_right);
			}
			else
			{
				new_task = get_task_from_tree(task, button_left);
			}
		}
		else if(button_get_pressed_ok())
		{
			new_task = get_task_from_tree(task, button_ok);
		}

		new_task = get_child_task(new_task);
	}

	return new_task;
}


void lcd_menu_update(void)
{
	menu_task_t task = get_new_task(menu_active);

	if(menu_active != task)
	{
		if(menu_tree[menu_active].parent != menu_tree[task].parent)
		{
			menu_tree[menu_tree[task].parent].reset_matrix();
			menu_tree[menu_tree[task].parent].draw();
		}
		else
		{
			menu_tree[task].reset_matrix();
		}
		menu_tree[task].draw();
		lcd_matrix_update(0, 0, 240, 128);
		menu_active = task;
	}
	else
	{
		if(menu_tree[menu_active].update != NULL)
		{
			if(!menu_tree[menu_active].update())
			{
				lcd_matrix_update(0, 0, 240, 128);
			}
		}
	}
}

void lcd_menu_draw(void)
{
	menu_tree[menu_active].draw();
	menu_active = get_child_task(menu_active);
	menu_tree[menu_active].draw();

	lcd_matrix_update(0, 0, 240, 128);
}

void lcd_menu_stop(void)
{
	lcd_body_graph_stop();
}
