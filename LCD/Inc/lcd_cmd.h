/*
 * lcd_cmd.h
 *
 *  Created on: 16.03.2020
 *      Author: Patrick
 */

#ifndef INC_LCD_CMD_H_
#define INC_LCD_CMD_H_

#define LCD_CURSOR_POINTER_SET					0x21
#define LCD_OFFSET_POINTER_SET					0x22
#define LCD_ADDRESS_POINTER_SET					0x24

#define LCD_TEXT_HOME_ADDR_SET					0x40
#define LCD_TEXT_AREA_SET						0x41
#define LCD_GRAPHIC_HOME_ADDR_SET				0x42
#define LCD_GRAPHIC_AREA_SET					0x43

#define LCD_MODE_SET							0x80

	#define LCD_MODE_OR							0x00
	#define LCD_MODE_EXOR						0x01
	#define LCD_MODE_AND						0x03
	#define LCD_MODE_TEXT_ATTRIBUTE				0x04

	#define LCD_MODE_INTERNAL_CG_ROM			0x00
	#define LCD_MODE_EXTERNAL_CG_ROM			0x08

#define LCD_DISPLAY_MODE						0x90

	#define LCD_DISPLAY_BLINK_ON				0x01
	#define LCD_DISPLAY_CURSUR_ON				0x02

	#define LCD_DISPLAY_TEXT_ON					0x04
	#define LCD_DISPLAY_GRAPHIC_ON				0x08

#define LCD_CURSOR_PATTERN_1_LINE				0xA0
#define LCD_CURSOR_PATTERN_2_LINES				0xA1
#define LCD_CURSOR_PATTERN_3_LINES				0xA2
#define LCD_CURSOR_PATTERN_4_LINES				0xA3
#define LCD_CURSOR_PATTERN_5_LINES				0xA4
#define LCD_CURSOR_PATTERN_6_LINES				0xA5
#define LCD_CURSOR_PATTERN_7_LINES				0xA6
#define LCD_CURSOR_PATTERN_8_LINES				0xA7

#define LCD_DATA_WRITE_AND_INC					0xC0
#define LCD_DATA_READ_AND_INC					0xC1
#define LCD_DATA_WRITE_AND_DEC					0xC2
#define LCD_DATA_READ_AND_DEC					0xC3
#define LCD_DATA_WRITE_AND_NONE					0xC4
#define LCD_DATA_READ_AND_NONE					0xC5

#define LCD_BIT									0xF0
	#define LCD_BIT_RESET						0x00
	#define LCD_BIT_SET							0x08

#endif /* INC_LCD_CMD_H_ */
