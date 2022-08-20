/*
 * lcd_driver.c
 *
 *  Created on: 08.02.2020
 *      Author: Patrick
 */

#include "main.h"


//static void GPIO_input_config(void)
//{
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//	/*Configure GPIO pins : DB4_Pin DB1_Pin DB2_Pin DB3_Pin */
//	GPIO_InitStruct.Pin = DB4_Pin|DB1_Pin|DB2_Pin|DB3_Pin;
//	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
//
//	/*Configure GPIO pins : DB6_Pin DB5_Pin DB7_Pin */
//	GPIO_InitStruct.Pin = DB6_Pin|DB5_Pin|DB7_Pin;
//	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
//
//	/*Configure GPIO pins : DB0_Pin */
//	GPIO_InitStruct.Pin = DB0_Pin;
//	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
//}
//
//static void GPIO_output_config(void)
//{
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//	/*Configure GPIO pins : DB4_Pin DB1_Pin DB2_Pin DB3_Pin */
//	GPIO_InitStruct.Pin = DB4_Pin|DB1_Pin|DB2_Pin|DB3_Pin;
//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
//
//	/*Configure GPIO pins : DB6_Pin DB5_Pin DB7_Pin */
//	GPIO_InitStruct.Pin = DB6_Pin|DB5_Pin|DB7_Pin;
//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
//
//	/*Configure GPIO pins : DB0_Pin */
//	GPIO_InitStruct.Pin = DB0_Pin;
//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
//
//	HAL_GPIO_WritePin(DB0_GPIO_Port, DB0_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(DB1_GPIO_Port, DB1_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(DB2_GPIO_Port, DB2_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(DB3_GPIO_Port, DB3_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(DB4_GPIO_Port, DB4_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(DB5_GPIO_Port, DB5_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(DB6_GPIO_Port, DB6_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(DB7_GPIO_Port, DB7_Pin, GPIO_PIN_RESET);
//}


uint8_t lcd_status_read(void)
{
//	uint8_t data = 0;
//
//	GPIO_input_config();
//
//	__asm("NOP");
////	__asm("NOP");
////	__asm("NOP");
//
//	HAL_GPIO_WritePin(GLCD_CD_GPIO_Port, GLCD_CD_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GLCD_WR_GPIO_Port, GLCD_WR_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GLCD_RD_GPIO_Port, GLCD_RD_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GLCD_CE_GPIO_Port, GLCD_CE_Pin, GPIO_PIN_RESET);
//
//	uint8_t d0 = HAL_GPIO_ReadPin(DB0_GPIO_Port, DB0_Pin);
//	uint8_t d1 = HAL_GPIO_ReadPin(DB1_GPIO_Port, DB1_Pin);
//	uint8_t d2 = HAL_GPIO_ReadPin(DB2_GPIO_Port, DB2_Pin);
//	uint8_t d3 = HAL_GPIO_ReadPin(DB3_GPIO_Port, DB3_Pin);
//	uint8_t d4 = HAL_GPIO_ReadPin(DB4_GPIO_Port, DB4_Pin);
//	uint8_t d5 = HAL_GPIO_ReadPin(DB5_GPIO_Port, DB5_Pin);
//	uint8_t d6 = HAL_GPIO_ReadPin(DB6_GPIO_Port, DB6_Pin);
//	uint8_t d7 = HAL_GPIO_ReadPin(DB7_GPIO_Port, DB7_Pin);
//
//	data |= d0 << 0;
//	data |= d1 << 1;
//	data |= d2 << 2;
//	data |= d3 << 3;
//	data |= d4 << 4;
//	data |= d5 << 5;
//	data |= d6 << 6;
//	data |= d7 << 7;
//
//	HAL_GPIO_WritePin(GLCD_CE_GPIO_Port, GLCD_CE_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GLCD_WR_GPIO_Port, GLCD_WR_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GLCD_RD_GPIO_Port, GLCD_RD_Pin, GPIO_PIN_SET);
//
//	__asm("NOP");
//
//	HAL_GPIO_WritePin(GLCD_CD_GPIO_Port, GLCD_CD_Pin, GPIO_PIN_SET);
//
//	__asm("NOP");
//
//	GPIO_output_config();

	return 0x23;
}

uint8_t lcd_data_write(uint8_t data)
{
	if((lcd_status_read() & 0x23) != 0x23)
	{
		return 1;
	}

	__disable_irq();

	HAL_GPIO_WritePin(DB0_GPIO_Port, GLCD_DB0_Pin, data & (1 << 0));
	HAL_GPIO_WritePin(DB1_GPIO_Port, GLCD_DB1_Pin, data & (1 << 1));
	HAL_GPIO_WritePin(DB2_GPIO_Port, GLCD_DB2_Pin, data & (1 << 2));
	HAL_GPIO_WritePin(DB3_GPIO_Port, GLCD_DB3_Pin, data & (1 << 3));
	HAL_GPIO_WritePin(DB4_GPIO_Port, GLCD_DB4_Pin, data & (1 << 4));
	HAL_GPIO_WritePin(DB5_GPIO_Port, GLCD_DB5_Pin, data & (1 << 5));
	HAL_GPIO_WritePin(DB6_GPIO_Port, GLCD_DB6_Pin, data & (1 << 6));
	HAL_GPIO_WritePin(DB7_GPIO_Port, GLCD_DB7_Pin, data & (1 << 7));

	HAL_GPIO_WritePin(GLCD_CD_GPIO_Port, GLCD_CD_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_WR_GPIO_Port, GLCD_WR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_RD_GPIO_Port, GLCD_RD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GLCD_CE_GPIO_Port, GLCD_CE_Pin, GPIO_PIN_RESET);

	for(uint8_t i = 0; i < 100; i++)
		__asm("NOP");

	HAL_GPIO_WritePin(GLCD_CE_GPIO_Port, GLCD_CE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GLCD_WR_GPIO_Port, GLCD_WR_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GLCD_RD_GPIO_Port, GLCD_RD_Pin, GPIO_PIN_SET);

	for(uint8_t i = 0; i < 100; i++)
		__asm("NOP");

	HAL_GPIO_WritePin(GLCD_CD_GPIO_Port, GLCD_CD_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(DB0_GPIO_Port, GLCD_DB0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB1_GPIO_Port, GLCD_DB1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB2_GPIO_Port, GLCD_DB2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB3_GPIO_Port, GLCD_DB3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB4_GPIO_Port, GLCD_DB4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB5_GPIO_Port, GLCD_DB5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB6_GPIO_Port, GLCD_DB6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB7_GPIO_Port, GLCD_DB7_Pin, GPIO_PIN_RESET);

	__enable_irq();

	return 0;
}

uint8_t lcd_cmd_write(uint8_t data)
{
	if((lcd_status_read() & 0x23) != 0x23)
	{
		return 1;
	}

	__disable_irq();

	HAL_GPIO_WritePin(DB0_GPIO_Port, GLCD_DB0_Pin, data & (1 << 0));
	HAL_GPIO_WritePin(DB1_GPIO_Port, GLCD_DB1_Pin, data & (1 << 1));
	HAL_GPIO_WritePin(DB2_GPIO_Port, GLCD_DB2_Pin, data & (1 << 2));
	HAL_GPIO_WritePin(DB3_GPIO_Port, GLCD_DB3_Pin, data & (1 << 3));
	HAL_GPIO_WritePin(DB4_GPIO_Port, GLCD_DB4_Pin, data & (1 << 4));
	HAL_GPIO_WritePin(DB5_GPIO_Port, GLCD_DB5_Pin, data & (1 << 5));
	HAL_GPIO_WritePin(DB6_GPIO_Port, GLCD_DB6_Pin, data & (1 << 6));
	HAL_GPIO_WritePin(DB7_GPIO_Port, GLCD_DB7_Pin, data & (1 << 7));

	HAL_GPIO_WritePin(GLCD_CD_GPIO_Port, GLCD_CD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GLCD_WR_GPIO_Port, GLCD_WR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_RD_GPIO_Port, GLCD_RD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GLCD_CE_GPIO_Port, GLCD_CE_Pin, GPIO_PIN_RESET);

	for(uint8_t i = 0; i < 100; i++)
		__asm("NOP");

	HAL_GPIO_WritePin(GLCD_CE_GPIO_Port, GLCD_CE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GLCD_WR_GPIO_Port, GLCD_WR_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GLCD_RD_GPIO_Port, GLCD_RD_Pin, GPIO_PIN_SET);

	for(uint8_t i = 0; i < 100; i++)
		__asm("NOP");

	HAL_GPIO_WritePin(GLCD_CD_GPIO_Port, GLCD_CD_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(DB0_GPIO_Port, GLCD_DB0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB1_GPIO_Port, GLCD_DB1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB2_GPIO_Port, GLCD_DB2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB3_GPIO_Port, GLCD_DB3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB4_GPIO_Port, GLCD_DB4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB5_GPIO_Port, GLCD_DB5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB6_GPIO_Port, GLCD_DB6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DB7_GPIO_Port, GLCD_DB7_Pin, GPIO_PIN_RESET);

	__enable_irq();

	return 0;
}


void lcd_reset(void)
{
	HAL_GPIO_WritePin(GLCD_RESET_GPIO_Port, GLCD_RESET_Pin, GPIO_PIN_RESET);
	__asm("NOP");__asm("NOP");__asm("NOP");
	__asm("NOP");__asm("NOP");__asm("NOP");
	__asm("NOP");__asm("NOP");__asm("NOP");
	__asm("NOP");__asm("NOP");__asm("NOP");
	__asm("NOP");__asm("NOP");__asm("NOP");
	__asm("NOP");__asm("NOP");__asm("NOP");
	HAL_GPIO_WritePin(GLCD_RESET_GPIO_Port, GLCD_RESET_Pin, GPIO_PIN_SET);
}

void lcd_set_font(void)
{
	HAL_GPIO_WritePin(GLCD_FONT_GPIO_Port, GLCD_FONT_Pin, GPIO_PIN_RESET);
}
