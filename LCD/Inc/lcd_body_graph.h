/*
 * lcd_body_graph.h
 *
 *  Created on: 15.03.2020
 *      Author: Patrick
 */

#ifndef INC_LCD_BODY_GRAPH_H_
#define INC_LCD_BODY_GRAPH_H_

#include <stdint.h>

uint8_t lcd_body_graph_draw(void);
uint8_t lcd_body_graph_update(void);
uint8_t lcd_body_graph_trigger_up(void);
uint8_t lcd_body_graph_trigger_down(void);

void lcd_body_graph_stop(void);

#endif /* INC_LCD_BODY_GRAPH_H_ */
