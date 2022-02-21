/*
 * lcd_config.h
 *
 *  Created on: 24.02.2020
 *      Author: Patrick
 */

#ifndef INC_LCD_CONFIG_H_
#define INC_LCD_CONFIG_H_

#define NUMBER_OF_LINES			128										// number of Pixel rows
#define PIXELS_PER_LINE			240										// number of Pixels in one row
#define FONT_WIDTH				8										// number of Pixels for one column

#define OFFSET_REGISTER			2
#define EXTERNAL_CG_HOME		(OFFSET_REGISTER << 11)

// TEXT
#define TEXT_HOME				0										// Start address of Text area
#define TEXT_AREA				(PIXELS_PER_LINE / FONT_WIDTH)			// number of columns for text area
#define TEXT_SIZE				(TEXT_AREA * (NUMBER_OF_LINES/8))		// number of characters in text area

// GRAPHIC
#define GRAPHIC_HOME			0 //(TEXT_HOME + TEXT_SIZE)				// Start address of graphic area
#define GRAPHIC_AREA			(PIXELS_PER_LINE / FONT_WIDTH)			// number of columns for graphics area
#define GRAPHIC_SIZE	 		(GRAPHIC_AREA * NUMBER_OF_LINES)		// number of bytes in graphic area

#endif /* INC_LCD_CONFIG_H_ */
