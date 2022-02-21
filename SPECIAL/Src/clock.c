/*
 * clock.c
 *
 *  Created on: 13.06.2019
 *      Author: Patrick
 */

#include <stdint.h>

#define CLOCK_STATUS_NONE		(0)
#define CLOCK_STATUS_CHANGED	(1)

uint8_t msec = 0;
uint8_t sec = 0;
uint8_t min = 0;
uint8_t hour = 0;

uint8_t clock_status = CLOCK_STATUS_NONE;


void clock_inc()
{
	msec++;

	if(msec >= 10)
	{
		sec++;
		msec = 0;

		if(sec >= 60)
		{
			min++;
			sec = 0;

			if(min >= 60)
			{
				hour++;
				min = 0;
			}
		}
	}

	clock_status = CLOCK_STATUS_CHANGED;
}

void clock_set_msec(uint8_t value)
{
	if(msec < 10)
		msec = value;

	clock_status = CLOCK_STATUS_CHANGED;
}

void clock_set_sec(uint8_t value)
{
	if(sec < 60)
		sec = value;

	clock_status = CLOCK_STATUS_CHANGED;
}

void clock_set_min(uint8_t value)
{
	if(min < 60)
		min = value;

	clock_status = CLOCK_STATUS_CHANGED;
}

void clock_set_hour(uint8_t value)
{
	// if(hour < 24)		// TODO how much hours should be allow to save.
	hour = value;

	clock_status = CLOCK_STATUS_CHANGED;
}

void clock_reset(void)
{
	clock_set_msec(0);
	clock_set_sec(0);
	clock_set_min(0);
	clock_set_hour(0);

	clock_status = CLOCK_STATUS_CHANGED;
}

uint8_t clock_get_msec(void)
{
	return msec;
}

uint8_t clock_get_sec(void)
{
	return sec;
}

uint8_t clock_get_min(void)
{
	return min;
}

uint8_t clock_get_hour(void)
{
	return hour;
}

void clock_set_status(void)
{
	clock_status = CLOCK_STATUS_CHANGED;
}

uint8_t clock_get_status(void)
{
	if(clock_status == CLOCK_STATUS_CHANGED)
	{
		return 0;
	}

	return 1;
}

void clock_reset_status(void)
{
	clock_status = CLOCK_STATUS_NONE;
}
