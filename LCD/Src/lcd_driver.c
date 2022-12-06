/*
 * lcd_driver.c
 *
 *  Created on: 08.02.2020
 *      Author: Patrick
 */

#include "main.h"


uint8_t lcd_data_write(uint8_t data)
{
	__disable_irq();

	HAL_GPIO_WritePin(GLCD_DB0_GPIO_Port, GLCD_DB0_Pin, data & (1 << 0));
	HAL_GPIO_WritePin(GLCD_DB1_GPIO_Port, GLCD_DB1_Pin, data & (1 << 1));
	HAL_GPIO_WritePin(GLCD_DB2_GPIO_Port, GLCD_DB2_Pin, data & (1 << 2));
	HAL_GPIO_WritePin(GLCD_DB3_GPIO_Port, GLCD_DB3_Pin, data & (1 << 3));
	HAL_GPIO_WritePin(GLCD_DB4_GPIO_Port, GLCD_DB4_Pin, data & (1 << 4));
	HAL_GPIO_WritePin(GLCD_DB5_GPIO_Port, GLCD_DB5_Pin, data & (1 << 5));
	HAL_GPIO_WritePin(GLCD_DB6_GPIO_Port, GLCD_DB6_Pin, data & (1 << 6));
	HAL_GPIO_WritePin(GLCD_DB7_GPIO_Port, GLCD_DB7_Pin, data & (1 << 7));

	HAL_GPIO_WritePin(GLCD_CD_GPIO_Port, GLCD_CD_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_WR_GPIO_Port, GLCD_WR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_CE_GPIO_Port, GLCD_CE_Pin, GPIO_PIN_RESET);

	for(uint8_t i = 0; i < 100; i++)
		__asm("NOP");

	HAL_GPIO_WritePin(GLCD_CE_GPIO_Port, GLCD_CE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GLCD_WR_GPIO_Port, GLCD_WR_Pin, GPIO_PIN_SET);

	for(uint8_t i = 0; i < 100; i++)
		__asm("NOP");

	HAL_GPIO_WritePin(GLCD_CD_GPIO_Port, GLCD_CD_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GLCD_DB0_GPIO_Port, GLCD_DB0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB1_GPIO_Port, GLCD_DB1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB2_GPIO_Port, GLCD_DB2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB3_GPIO_Port, GLCD_DB3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB4_GPIO_Port, GLCD_DB4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB5_GPIO_Port, GLCD_DB5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB6_GPIO_Port, GLCD_DB6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB7_GPIO_Port, GLCD_DB7_Pin, GPIO_PIN_RESET);

	__enable_irq();

	return 0;
}

uint8_t lcd_cmd_write(uint8_t data)
{
	__disable_irq();

	HAL_GPIO_WritePin(GLCD_DB0_GPIO_Port, GLCD_DB0_Pin, data & (1 << 0));
	HAL_GPIO_WritePin(GLCD_DB1_GPIO_Port, GLCD_DB1_Pin, data & (1 << 1));
	HAL_GPIO_WritePin(GLCD_DB2_GPIO_Port, GLCD_DB2_Pin, data & (1 << 2));
	HAL_GPIO_WritePin(GLCD_DB3_GPIO_Port, GLCD_DB3_Pin, data & (1 << 3));
	HAL_GPIO_WritePin(GLCD_DB4_GPIO_Port, GLCD_DB4_Pin, data & (1 << 4));
	HAL_GPIO_WritePin(GLCD_DB5_GPIO_Port, GLCD_DB5_Pin, data & (1 << 5));
	HAL_GPIO_WritePin(GLCD_DB6_GPIO_Port, GLCD_DB6_Pin, data & (1 << 6));
	HAL_GPIO_WritePin(GLCD_DB7_GPIO_Port, GLCD_DB7_Pin, data & (1 << 7));

	HAL_GPIO_WritePin(GLCD_CD_GPIO_Port, GLCD_CD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GLCD_WR_GPIO_Port, GLCD_WR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_CE_GPIO_Port, GLCD_CE_Pin, GPIO_PIN_RESET);

	for(uint8_t i = 0; i < 100; i++)
		__asm("NOP");

	HAL_GPIO_WritePin(GLCD_CE_GPIO_Port, GLCD_CE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GLCD_WR_GPIO_Port, GLCD_WR_Pin, GPIO_PIN_SET);

	for(uint8_t i = 0; i < 100; i++)
		__asm("NOP");

	HAL_GPIO_WritePin(GLCD_CD_GPIO_Port, GLCD_CD_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GLCD_DB0_GPIO_Port, GLCD_DB0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB1_GPIO_Port, GLCD_DB1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB2_GPIO_Port, GLCD_DB2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB3_GPIO_Port, GLCD_DB3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB4_GPIO_Port, GLCD_DB4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB5_GPIO_Port, GLCD_DB5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB6_GPIO_Port, GLCD_DB6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLCD_DB7_GPIO_Port, GLCD_DB7_Pin, GPIO_PIN_RESET);

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
