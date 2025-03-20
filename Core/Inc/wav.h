/*
 * wav.h
 *
 *  Created on: Apr 18, 2024
 *      Author: pinkylo
 */

#ifndef INC_WAV_H_
#define INC_WAV_H_

#include "fatfs.h"
#include "lcd.h"

 typedef enum{
	UNKNOWN,
	HALF_COMPLETED,
	FULL_COMPLETED
} Callback_Result_t;


void play_audio();
void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s);

#endif /* INC_WAV_H_ */
