/*
 * adc.c
 *
 *  Created on: 14.07.2019
 *      Author: Patrick
 */

#include <stdint.h>
#include <string.h>

#include "stm32f4xx_hal.h"

#include "buffer_lcd.h"
#include "buffer_usb.h"
#include "measure_period.h"

#define COUNT_FOR_MEAN		(11)

#define COUNT_OF_USED_ADC	(13)

#define ADC1_ENABLE			(1)
#define ADC1_ENABLE_POS		(0)
#define ADC_ENABLE			(ADC1_ENABLE << ADC1_ENABLE_POS)

#define ADC1_DATA_VALID		(0)
#define ADC1_VALID_POS		(0)
#define ADC_DATA_VALID		(ADC1_DATA_VALID << ADC1_VALID_POS)

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

uint8_t adc_enable = ADC_ENABLE;
uint8_t adc_data = ADC_DATA_VALID;

uint16_t adc_value[COUNT_OF_USED_ADC] = {0};

uint8_t adc_value_index = 0;
uint16_t adc_value_buffer[COUNT_FOR_MEAN][COUNT_OF_USED_ADC] = {0};


static void __sort_bubble(uint16_t *array, size_t array_length, size_t size)
{
	while(size--)
	{
		for(uint8_t i = 1; i <= size; i++)
		{
			uint16_t *tmp1 = array + array_length * (i - 1);
			uint16_t *tmp2 = array + array_length * i;

			if(tmp1[0] > tmp2[0])
			{
				uint16_t temp = *tmp2;
				*tmp2 = *tmp1;
				*tmp1 = temp;
			}
		}
	}
}

void adc_transfer_data_to_buffer(void)
{
	if(!measure_period_get_status_started())
	{
		if(HAL_IS_BIT_SET(adc_data, ADC_ENABLE))
		{
			memcpy(adc_value_buffer[adc_value_index], adc_value, sizeof(adc_value_buffer[0]));
			adc_data = 0;

			adc_value_index++;

			if(adc_value_index >= COUNT_FOR_MEAN)
			{
				for(uint8_t i = 0; i < COUNT_OF_USED_ADC; i++)
				{
					__sort_bubble((uint16_t *)&adc_value_buffer[0][i], sizeof(adc_value_buffer[0]) / sizeof(adc_value_buffer[0][0]), sizeof(adc_value_buffer) / sizeof(adc_value_buffer[0]));
				}

				buffer_lcd_set_value((uint32_t *)&adc_value_buffer[5], COUNT_OF_USED_ADC);
				buffer_usb_set_value((uint32_t *)&adc_value_buffer[5], COUNT_OF_USED_ADC);
				adc_value_index = 0;

				measure_period_set_status_finished();
			}
			else
			{
				measure_period_set_status_waiting();
			}
		}
	}
}

void adc_dma_start(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adc_value[0], COUNT_OF_USED_ADC);
}

void __adc_dma_stop(void)
{
	HAL_ADC_Stop_DMA(&hadc1);
}

void adc_stop(void)
{
	adc_value_index = 0;
	__adc_dma_stop();
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc == &hadc1)
	{
		SET_BIT(adc_data, 1 << ADC1_ENABLE_POS);
	}
}
