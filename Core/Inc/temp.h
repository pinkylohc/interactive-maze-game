/*
 * temp.h
 *
 *  Created on: Apr 13, 2024
 *      Author: pinkylo
 */

#ifndef INC_TEMP_H_
#define INC_TEMP_H_

void delay (uint32_t us);
void gpio_set_input (void);
void gpio_set_output (void);
uint8_t ds18b20_init (void);
void write_ds (uint8_t data);
uint8_t read_ds (void);
float temp_value();


#endif /* INC_TEMP_H_ */
