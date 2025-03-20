/*
 * max7129.c
 *
 *  Created on: Apr 23, 2024
 *      Author: pinkylo
 */


#include "max7219.h"

char font[10][5]={
		{0b00111110,0b01010001,0b01001001,0b01000101,0b00111110}, //0
		{0b00000000,0b01000010,0b01111111,0b01000000,0b00000000}, // 1
		{0b01000010,0b01100001,0b01010001,0b01001001,0b01000110}, // 2
		{0b00100001,0b01000001,0b01000101,0b01001011,0b00110001}, // 3
		{0b00011000,0b00010100,0b00010010,0b01111111,0b00010000}, // 4
		{0b00100111,0b01000101,0b01000101,0b01000101,0b00111001}, // 5
		{0b00111100,0b01001010,0b01001001,0b01001001,0b00110000}, // 6
		{0b00000011,0b01110001,0b00001001,0b00000101,0b00000011}, // 7
		{0b00110110,0b01001001,0b01001001,0b01001001,0b00110110}, // 8
		{0b00000110,0b01001001,0b01001001,0b00101001,0b00011110}, // 9
};


#define CS_SET() 	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)
#define CS_RESET() 	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET)

extern volatile bool fail;

void print_digit(int number){
	int ten_digit = number/10;
	int last_digit = number%10;

	//if ten digit == 0, print empty


	uint8_t col = 0x02;
	max7219_SendData(0x01, 0x00, 0x01, 0x00);
	for (col = 2; col < 7; ++col){
		max7219_SendData(col, font[last_digit][col-2], col, font[ten_digit][col-2]);
	}
	max7219_SendData(0x08, 0x00, 0x08, 0x00);


}


//datasheet - initialize the dot matrix
void max7219_Init()
{
	max7219_SendData(0x09, 0x00, 0x09, 0x00);	//decode mode
	max7219_SendData(0x0a, 0x01, 0x0a, 0x01);	//intensity
	max7219_SendData(0x0b, 0x07, 0x0b, 0x07);	//scan limit
	max7219_SendData(0x0c, 0x01, 0x0c, 0x01);	//display on
	max7219_SendData(0x0f, 0x00, 0x0f, 0x00);	//disable display test
	max7219_Clean();
}

//clean up the dot matrix with no dot
void max7219_Clean()
{
	uint8_t clear = 0x00;

	for (int i = 0; i < 8; ++i)
	{
		max7219_SendData(i + 1, clear, i + 1, clear);
	}
}

//send data to the two dot matrix
//addr1, data1 for the second matrix
//addr2, data2 for the first matrix
void max7219_SendData(uint8_t addr1, uint8_t data1, uint8_t addr2, uint8_t data2)
{
	CS_SET();
	HAL_SPI_Transmit_DMA(&hspi1, &addr1, 1);
	HAL_SPI_Transmit_DMA(&hspi1, &data1, 1);
	HAL_SPI_Transmit_DMA(&hspi1, &addr2, 1);
	HAL_SPI_Transmit_DMA(&hspi1, &data2, 1);
	CS_RESET();
}

