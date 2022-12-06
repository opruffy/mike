/*
 * measure.c
 *
 *  Created on: 11.04.2020
 *      Author: Patrick
 */

#include <stdint.h>

#define MEASURE_MODE_STOP			(0)
#define MEASURE_MODE_START			(1)
#define MEASURE_MODE_RUNNING		(2)
#define MEASURE_MODE_PAUSE			(3)

#define MEASURE_MODE_STATUS_NONE	(0)
#define MEASURE_MODE_STATUS_CHANGED	(1)

uint8_t measure_mode = MEASURE_MODE_STOP;
uint8_t measure_mode_status = MEASURE_MODE_STATUS_NONE;


// MEASURE MODE STATUS
// -------------------
void measure_mode_status_set_changed(void)
{
	measure_mode_status = MEASURE_MODE_STATUS_CHANGED;
}

uint8_t measure_mode_status_get_changed(void)
{
	if(measure_mode_status == MEASURE_MODE_STATUS_CHANGED)
	{
		return 0;
	}

	return 1;
}

/*
 * call update when
 * - starting never
 * - running after lcd update
 * - pause in main
 * - stop in main
 */
void measure_mode_status_update(void)
{
	if(measure_mode_status == MEASURE_MODE_STATUS_CHANGED)
	{
		measure_mode_status = MEASURE_MODE_STATUS_NONE;
	}
}

// MEASURE MODE
// ------------
void measure_set_mode_start(void)
{
	if((measure_mode == MEASURE_MODE_STOP) || (measure_mode == MEASURE_MODE_PAUSE))
	{
		measure_mode = MEASURE_MODE_START;
		measure_mode_status = MEASURE_MODE_STATUS_CHANGED;
	}
}

uint8_t measure_get_mode_start(void)
{
	if(measure_mode == MEASURE_MODE_START)
	{
		return 0;
	}

	return 1;
}

void measure_set_mode_running(void)
{
	if(measure_mode == MEASURE_MODE_START)
	{
		measure_mode = MEASURE_MODE_RUNNING;
		measure_mode_status = MEASURE_MODE_STATUS_CHANGED;
	}
}

uint8_t measure_get_mode_running(void)
{
	if(measure_mode == MEASURE_MODE_RUNNING)
	{
		return 0;
	}

	return 1;
}

void measure_set_mode_pause(void)
{
	if((measure_mode == MEASURE_MODE_START) || (measure_mode == MEASURE_MODE_RUNNING))
	{
		measure_mode = MEASURE_MODE_PAUSE;
		measure_mode_status = MEASURE_MODE_STATUS_CHANGED;
	}
}

uint8_t measure_get_mode_pause(void)
{
	if(measure_mode == MEASURE_MODE_PAUSE)
	{
		return 0;
	}

	return 1;
}

void measure_set_mode_stop(void)
{
	measure_mode = MEASURE_MODE_STOP;
	measure_mode_status = MEASURE_MODE_STATUS_CHANGED;
}

uint8_t measure_get_mode_stop(void)
{
	if(measure_mode == MEASURE_MODE_STOP)
	{
		return 0;
	}

	return 1;
}
