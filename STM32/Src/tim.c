/*
 * tim.c
 *
 *  Created on: 18.03.2020
 *      Author: Patrick
 */

#include "stm32f4xx_hal.h"

#include "adc.h"
#include "clock.h"
#include "lcd.h"
#include "measure.h"
#include "measure_period.h"
#include "usb.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim2)
	{
		usb_update();
	}
	else if(htim == &htim3)
	{
	 	lcd_update();
	 	measure_mode_status_update();
	}
	else if(htim == &htim6)
	{
		if(!measure_get_mode_running())
		{
			clock_inc();
			measure_period_update_status();

			if(!measure_period_get_status_ready())
			{
				adc_dma_start();
				measure_period_set_status_started();
			}
		}
	}
}

void tim_start_irq(void)
{
	if(!measure_get_mode_start())
	{
		HAL_TIM_Base_Start_IT(&htim6);
		adc_dma_start();
		measure_period_set_status_started();
		measure_set_mode_running();
	}
}
