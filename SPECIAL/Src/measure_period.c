/*
 * measure_period.c
 *
 *  Created on: 13.07.2021
 *      Author: Patrick
 */

#include <stdint.h>

#include "measure.h"

#define TIM_PERIOD_MODE_1MIN		(0)
#define TIM_PERIOD_MODE_DEBUG		(1)

#define MEASURE_STATUS_READY		(0)
#define MEASURE_STATUS_FINISHED		(1)
#define MEASURE_STATUS_WAITING		(2)
#define MEASURE_STATUS_STARTED		(3)

// get median value of measurements
#define TIM_PERIOD_VALUE_1MIN		(600)
#define TIM_PERIOD_VALUE_DEBUG		(300)		// 30 sec.

// get measurement
#define TIM_PERIOD_MEASURE_5SEC		(50)
#define TIM_PERIOD_MEASURE_DEBUG	(25)		// 2,5 sec.

uint8_t measure_period_mode = TIM_PERIOD_MODE_DEBUG;		// TODO change to normal MODE.
uint8_t measure_period_status = MEASURE_STATUS_WAITING;
uint16_t measure_period_count = 0;

typedef struct
{
	uint32_t period_value;
	uint32_t period_get_measurement;
	char period_text[8];
}measure_info_t;

measure_info_t measure_period_info[] =
{
		{
			.period_value = TIM_PERIOD_VALUE_1MIN,
			.period_get_measurement = TIM_PERIOD_MEASURE_5SEC,
			.period_text = "60 sec.",
		},
		{
			.period_value = TIM_PERIOD_VALUE_DEBUG,
			.period_get_measurement = TIM_PERIOD_MEASURE_DEBUG,
			.period_text = "30 sec.",
		},
};


// MEASURE PERIOD
// --------------
uint32_t measure_period_get_current_value(void)
{
	return measure_period_info[measure_period_mode].period_value;
}

void measure_period_set_mode(uint8_t _index)
{
	measure_set_mode_stop();
	measure_period_mode = _index;
}

uint8_t measure_period_get_current_mode(void)
{
	return measure_period_mode;
}

uint8_t measure_period_get_previous_mode(uint8_t _index)
{
	if(_index == 0)
	{
		return (sizeof(measure_period_info) / sizeof(measure_period_info[0]) - 1);
	}

	_index--;
	return _index;
}

uint8_t measure_period_get_next_mode(uint8_t _index)
{
	_index++;
	if(_index > (sizeof(measure_period_info) / sizeof(measure_period_info[0]) - 1))
	{
		return 0;
	}

	return _index;
}

char * measure_period_get_text(uint8_t _index)
{
	return measure_period_info[_index].period_text;
}

// MEASURE PERIOD STATUS
// ---------------------
void measure_period_set_status_waiting(void)
{
	measure_period_status = MEASURE_STATUS_WAITING;
}

uint8_t measure_period_get_status_ready(void)
{
	if(measure_period_status == MEASURE_STATUS_READY)
	{
		return 0;
	}

	return 1;
}

void measure_period_set_status_started(void)
{
	measure_period_status = MEASURE_STATUS_STARTED;
}

uint8_t measure_period_get_status_started(void)
{
	if(measure_period_status == MEASURE_STATUS_STARTED)
	{
		return 0;
	}

	return 1;
}

void measure_period_set_status_finished(void)
{
	measure_period_status = MEASURE_STATUS_FINISHED;
}

void measure_period_reset_status(void)
{
	measure_period_status = MEASURE_STATUS_WAITING;
	measure_period_count = 0;
}

/*
uint8_t measure_period_get_status_finished(void)
{
	uint8_t tmp = 0;

	if(measure_period_status == MEASURE_STATUS_FINISHED)
	{
		tmp = 1;
	}

	return tmp;
}
*/

uint8_t measure_period_update_status(void)
{
	measure_period_count++;

	if(measure_period_status == MEASURE_STATUS_FINISHED)
	{
		if(measure_period_count == measure_period_info[measure_period_mode].period_value)
		{
			measure_period_set_status_waiting();
			measure_period_count = 0;
		}
	}
	if(measure_period_status == MEASURE_STATUS_WAITING)
	{
		if(!(measure_period_count % measure_period_info[measure_period_mode].period_get_measurement))
		{
			measure_period_status = MEASURE_STATUS_READY;
		}
	}

	return 0;
}
