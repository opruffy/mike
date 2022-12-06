/*
 * adc.h
 *
 *  Created on: 14.07.2019
 *      Author: Patrick
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

void adc_transfer_data_to_buffer(void);

void adc_dma_start(void);
void adc_stop(void);

#endif /* INC_ADC_H_ */
