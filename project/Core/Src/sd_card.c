/*
 * sd_card.c
 *
 *  Created on: Apr 11, 2024
 *      Author: pinkylo
 */


#include "sd_card.h"

extern uint8_t status, level, duration;

/*
 * win/lose  -  status (0win, 1lose)
 * no of task finished/failure  -
 * difficulty level  - level
 * round time - duration
 */

void game_record(){
	  //test sd card write
	  FATFS myFATFS;
	  FIL myFILE;
	  char str[30];
	  //UINT numberofbytes;
	  char myPath[] = "game.txt\0";

	  FRESULT res;
	  res = f_mount(&myFATFS,SDPath,1);

	  if (res == FR_OK){
	  LCD_DrawString(0,0,"start",RED);
	  HAL_Delay(100);
	  f_open(&myFILE, myPath, FA_WRITE | FA_OPEN_ALWAYS);
	  f_lseek(&myFILE, f_size(&myFILE));
	  //f_write(&myFILE, array, sizeof(array), &numberofbytes);
	  //write record
	  f_puts("\n\n", &myFILE);

	  if(status == 0) f_puts("win! ^_^\n", &myFILE);
	  else f_puts("lose! T_T\n", &myFILE);

	  uint8_t min = duration/60;
	  uint8_t sec = duration%60;
	  sprintf(str, "time spend: %u:%u \n",min, sec);
	  f_puts(str, &myFILE);

	  if(level == 1) f_puts("difficulty level: easy", &myFILE);
	  else if(level == 2) f_puts("difficulty level: medium", &myFILE);
	  else if(level == 3) f_puts("difficulty level: hard", &myFILE);


	  f_close(&myFILE);
	  LCD_DrawString(0,0,"end",RED);
	  f_mount(&myFATFS, " ", 0);

	  }else LCD_DrawString(0,0,"failure",RED);

	 //testing
	/*FATFS myFATFS;
    FIL myFILE;
    UINT numberofbytes;
    char myPath[] = "game.txt\0";
    char myData[] = "123\0";
    FRESULT res;
    res = f_mount(&myFATFS,SDPath,1);
    if (res == FR_OK){
  	LCD_DrawString(0,0,"start",RED);
  	HAL_Delay(1000);
  	f_open(&myFILE, myPath, FA_WRITE | FA_OPEN_ALWAYS);
  	f_lseek(&myFILE, f_size(&myFILE));
  	f_puts("\n\n", &myFILE);
  	f_write(&myFILE, myData, sizeof(myData), &numberofbytes);
  	f_close(&myFILE);
  	LCD_DrawString(0,0,"end",RED);
    }else LCD_DrawString(0,0,"failure",RED);*/

}
