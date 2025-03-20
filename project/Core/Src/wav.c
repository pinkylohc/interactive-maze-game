/*
 * wav.c
 *
 *  Created on: Apr 18, 2024
 *      Author: pinkylo
 */


#include "wav.h"

extern I2S_HandleTypeDef hi2s2;

int16_t samples[3200];

FATFS fatfs;
FIL fil;
FRESULT fresult;

UINT fread_size = 0;
uint32_t recording_size = 0;
uint32_t played_size = 0;

Callback_Result_t callback_result = UNKNOWN;

void play_audio(char *filename){
 callback_result = UNKNOWN;
 fread_size = 0;
 recording_size = 0;
 played_size = 0;

 fresult = f_mount(&fatfs,SDPath,1);
  if (fresult != FR_OK) return;

  fresult = f_open(&fil, filename, FA_OPEN_EXISTING|FA_READ); // WIN3 & LOSE2.wav
  if (fresult != FR_OK) return;

  f_lseek(&fil, 40); //wav file header 40th byte -> size of file
  //LCD_DrawString(0,0,"recording seek", BLUE);

  f_read(&fil, &recording_size, 4, &fread_size);
  //LCD_DrawString(0,0,"recording size", BLUE);

  recording_size /= 2;	// 2 means 2B (16 bit per sample)

  f_read(&fil,samples, 6400, &fread_size);

  HAL_I2S_Transmit_DMA(&hi2s2,(uint16_t *) samples, 3200);

  //LCD_DrawString(0,0,"start   while", RED);

  while (1)
    {
  	  if(callback_result == HALF_COMPLETED)
  	  	  {
  	  		  f_read(&fil, samples, 3200, &fread_size);
  	  		  callback_result = UNKNOWN;
  	  	  }

  	  	  if(callback_result == FULL_COMPLETED)
  	  	  {
  	  		  f_read(&fil, &samples[1600], 3200, &fread_size);
  	  		  callback_result = UNKNOWN;
  	  	  }

  	  	  if(played_size >= recording_size)
  	  	  {
  	  		  HAL_I2S_DMAStop(&hi2s2);
  	  		//LCD_DrawString(0,0,"stop     ", RED);
  	  		f_close(&fil);
  	  		 f_mount(&fatfs," ",0);
  	  		break;
  	  	  }
    }
}

  void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
  {
  	callback_result = HALF_COMPLETED;
  }
  void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
  {
  	callback_result = FULL_COMPLETED;
  	played_size += 3200;
  }
