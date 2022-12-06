/*
 * button.c
 *
 *  Created on: 17.03.2020
 *      Author: Patrick
 */

#include "stm32f4xx_hal.h"

#include "main.h"

#define BUTTON_UP_POS						(0)
#define BUTTON_DOWN_POS						(1)
#define BUTTON_LEFT_POS						(2)
#define BUTTON_RIGHT_POS					(3)
#define BUTTON_OK_POS						(4)

#define BUTTON_UP_MASK						(1 << BUTTON_UP_POS)
#define BUTTON_DOWN_MASK					(1 << BUTTON_DOWN_POS)
#define BUTTON_LEFT_MASK					(1 << BUTTON_LEFT_POS)
#define BUTTON_RIGHT_MASK					(1 << BUTTON_RIGHT_POS)
#define BUTTON_OK_MASK						(1 << BUTTON_OK_POS)

uint8_t pressed_button = 0;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
		case UP_Pin:
			if(HAL_GPIO_ReadPin(UP_GPIO_Port, UP_Pin) != GPIO_PIN_RESET)
			{
				pressed_button |= BUTTON_UP_MASK;
			}
			break;
		case DOWN_Pin:
			if(HAL_GPIO_ReadPin(DOWN_GPIO_Port, DOWN_Pin) != GPIO_PIN_RESET)
			{
				pressed_button |= BUTTON_DOWN_MASK;
			}
			break;
		case LEFT_Pin:
			if(HAL_GPIO_ReadPin(LEFT_GPIO_Port, LEFT_Pin) != GPIO_PIN_RESET)
			{
				pressed_button |= BUTTON_LEFT_MASK;
			}
			break;
		case RIGHT_Pin:
			if(HAL_GPIO_ReadPin(RIGHT_GPIO_Port, RIGHT_Pin) != GPIO_PIN_RESET)
			{
				pressed_button |= BUTTON_RIGHT_MASK;
			}
			break;
		case PUSH_Pin:
			if(HAL_GPIO_ReadPin(PUSH_GPIO_Port, PUSH_Pin) != GPIO_PIN_RESET)
			{
				pressed_button |= BUTTON_OK_MASK;
			}
			break;
		default:
			break;

	}
}

uint8_t button_get_pressed_any(void)
{
	return pressed_button;
}

uint8_t button_get_pressed_up(void)
{
	if((pressed_button & BUTTON_UP_MASK) == BUTTON_UP_MASK)
	{
		pressed_button &= ~BUTTON_UP_MASK;
		return 1;
	}

	return 0;
}

uint8_t button_get_pressed_down(void)
{
	if((pressed_button & BUTTON_DOWN_MASK) == BUTTON_DOWN_MASK)
	{
		pressed_button &= ~BUTTON_DOWN_MASK;
		return 1;
	}

	return 0;
}

uint8_t button_get_pressed_left(void)
{
	if((pressed_button & BUTTON_LEFT_MASK) == BUTTON_LEFT_MASK)
	{
		pressed_button &= ~BUTTON_LEFT_MASK;
		return 1;
	}

	return 0;
}

uint8_t button_get_pressed_right(void)
{
	if((pressed_button & BUTTON_RIGHT_MASK) == BUTTON_RIGHT_MASK)
	{
		pressed_button &= ~BUTTON_RIGHT_MASK;
		return 1;
	}

	return 0;
}

uint8_t button_get_pressed_ok(void)
{
	if((pressed_button & BUTTON_OK_MASK) == BUTTON_OK_MASK)
	{
		pressed_button &= ~BUTTON_OK_MASK;
		return 1;
	}

	return 0;
}
