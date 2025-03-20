/*
 * temp.c
 *
 *  Created on: Apr 13, 2024
 *      Author: pinkylo
 */
#include "stm32f1xx_hal.h"
#include <stdlib.h>

uint8_t check =2, temp_l, temp_h;
uint16_t temp;
float temperature;
extern TIM_HandleTypeDef htim1;

void delay (uint32_t us)
{
    __HAL_TIM_SET_COUNTER(&htim1,0);
    while ((__HAL_TIM_GET_COUNTER(&htim1))<us);
}
GPIO_InitTypeDef GPIO_InitStruct;

void gpio_set_input (void)
{
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}


void gpio_set_output (void)
{
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}


uint8_t ds18b20_init (void)
{
	gpio_set_output ();   // set the pin as output
	HAL_GPIO_WritePin (GPIOC, GPIO_PIN_5, 0);  // pull the pin low
	delay (480);   // delay according to datasheet

	gpio_set_input ();    // set the pin as input
	delay (80);    // delay according to datasheet

	if (!(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_5)))    // if the pin is low i.e the presence pulse is there
	{
		delay (400);  // wait for 400 us
		return 0;
	}

	else
	{
		delay (400);
		return 1;
	}
}

void write_ds (uint8_t data)
{
	gpio_set_output ();   // set as output

	for (int i=0; i<8; i++)
	{

		if ((data & (1<<i))!=0)  // if the bit is high
		{
			// write 1

			gpio_set_output ();  // set as output
			HAL_GPIO_WritePin (GPIOC, GPIO_PIN_5, 0);  // pull the pin LOW
			delay (1);  // wait for  us

			gpio_set_input ();  // set as input
			delay (60);  // wait for 60 us
		}

		else  // if the bit is low
		{
			// write 0

			gpio_set_output ();
			HAL_GPIO_WritePin (GPIOC, GPIO_PIN_5, 0);  // pull the pin LOW
			delay (60);  // wait for 60 us

			gpio_set_input ();
		}
	}
}


uint8_t read_ds (void)
{
	uint8_t value=0;
	gpio_set_input ();

	for (int i=0;i<8;i++)
	{
		gpio_set_output ();   // set as output

		HAL_GPIO_WritePin (GPIOC, GPIO_PIN_5, 0);  // pull the data pin LOW
		delay (2);  // wait for 2 us

		gpio_set_input ();  // set as input
		if (HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_5))  // if the pin is HIGH
		{
			value |= 1<<i;  // read = 1
		}
		delay (60);  // wait for 60 us
	}
	return value;
}

float temp_value(){
	check = ds18b20_init ();
	write_ds (0xCC);  // skip ROM
	write_ds (0x44);  // convert t

	HAL_Delay (500);

	ds18b20_init ();
	write_ds (0xCC);  // skip ROM
	write_ds (0xBE);  // Read Scratchpad

	temp_l = read_ds();
	temp_h = read_ds();
	temp = (temp_h<<8)|temp_l;
	temperature = (float)temp/16;

	return temperature;

}
