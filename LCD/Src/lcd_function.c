/*
 * lcd_function.c
 *
 *  Created on: 08.03.2020
 *      Author: Patrick
 */

#include "lcd_driver.h"
#include "lcd_config.h"
#include "lcd_cmd.h"


static void set_data_16bit(uint8_t cmd, uint16_t data)
{
	lcd_data_write(data & 0xFF);
	lcd_data_write(data >> 8);

	lcd_cmd_write(cmd);
}

static void set_data_8bit(uint8_t cmd, uint8_t data)
{
	lcd_data_write(data);

	lcd_cmd_write(cmd);
}

static void set_address_pointer(uint16_t addr)
{
	set_data_16bit(LCD_ADDRESS_POINTER_SET, addr);
}

static void write_data(uint8_t data)
{
	set_data_8bit(LCD_DATA_WRITE_AND_INC, data);
}

// Clear text area
static void clear_text(void)
{
	set_address_pointer(TEXT_HOME);

	for(uint32_t i = 0; i < TEXT_SIZE; i++)
	{
		write_data(0);
	}
}

// Clear character generator area
static void clear_cg(void)
{
	set_address_pointer(EXTERNAL_CG_HOME);

	for(uint32_t i = 0; i < 256 * 8; i++)
	{
		write_data(0);
	}
}

// Clear graphic area
static void clear_graphic(uint8_t data)
{
	set_address_pointer(GRAPHIC_HOME);

	for(uint32_t i = 0; i < GRAPHIC_SIZE; i++)
	{
		write_data(data);
	}
}

static void clear_display(uint8_t data)
{
	clear_text();
	clear_cg();
	clear_graphic(data);
}


uint8_t lcd_initialize(void)
{
	lcd_reset();
	lcd_set_font();

	while((lcd_status_read() & 0x23) != 0x23);

	__asm("NOP");__asm("NOP");
	__asm("NOP");__asm("NOP");
	__asm("NOP");__asm("NOP");
	__asm("NOP");__asm("NOP");

	set_data_16bit(LCD_GRAPHIC_HOME_ADDR_SET, GRAPHIC_HOME);
	set_data_16bit(LCD_GRAPHIC_AREA_SET, GRAPHIC_AREA);
	set_data_16bit(LCD_TEXT_HOME_ADDR_SET, TEXT_HOME);
	set_data_16bit(LCD_TEXT_AREA_SET, TEXT_AREA);
	set_data_16bit(LCD_OFFSET_POINTER_SET, OFFSET_REGISTER);

	set_address_pointer(0);

	if(lcd_cmd_write(LCD_DISPLAY_MODE | LCD_DISPLAY_TEXT_ON | LCD_DISPLAY_GRAPHIC_ON))
	{
		return 7;
	}

	if(lcd_cmd_write(LCD_MODE_SET | LCD_MODE_OR | LCD_MODE_INTERNAL_CG_ROM))
	{
		return 8;
	}

	clear_display(0);

	lcd_cmd_write(LCD_DISPLAY_MODE | LCD_DISPLAY_GRAPHIC_ON);

	return 0;
}

uint8_t lcd_set_pixel(uint16_t x, uint16_t y)
{
	uint8_t setBit = LCD_BIT | LCD_BIT_SET | (7 - (x % 8));

	set_address_pointer(GRAPHIC_HOME + (uint16_t)(x / 8) + y * 30);

	if(lcd_cmd_write(setBit))
	{
		return 1;
	}

	return 0;
}

uint8_t lcd_clear_pixel(uint16_t x, uint16_t y)
{
	uint8_t setBit = LCD_BIT | LCD_BIT_RESET | (7 - (x % 8));

	set_address_pointer(GRAPHIC_HOME + (uint16_t)(x / 8) + y * 30);

	if(lcd_cmd_write(setBit))
	{
		return 1;
	}

	return 0;
}
