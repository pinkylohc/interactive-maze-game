/*
 * max7129.h
 *
 *  Created on: Apr 23, 2024
 *      Author: pinkylo
 */

#ifndef INC_MAX7219_H_
#define INC_MAX7219_H_

#include "main.h"
#include "stdbool.h"

#define NUMBER_OF_DIGITS	8
#define SPI_PORT			hspi1

extern SPI_HandleTypeDef 	SPI_PORT;



void max7219_Init();
void max7219_SendData(uint8_t addr1, uint8_t data1, uint8_t addr2, uint8_t data2);
void max7219_Clean(void);
void print_digit(int number);


#endif /* INC_MAX7219_H_ */
