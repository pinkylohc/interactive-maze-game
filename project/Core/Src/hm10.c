/*
 * hm10.c
 *
 *  Created on: Apr 27, 2024
 *      Author: pinkylo
 */

#include "hm10.h"

FATFS myFATFS;
FIL myFILE;
uint8_t lineToRead = 3; // Line number to read
uint8_t currentLine = 1; // Current line number
char buffer[100] = {0}; // Buffer to store the read line
char question[100];
char answer[100];

void get_question(){
  int num_odd_numbers = (41 - 1) / 2 + 1;
  int index = rand() % num_odd_numbers;
  int lineToRead = 1 + 2 * index;
  currentLine = 1;

  f_mount(&myFATFS,SDPath,1);
  f_open(&myFILE, "QUIZ.TXT", FA_OPEN_EXISTING|FA_READ);
  while (currentLine <= lineToRead+1) {
	  if (f_gets(buffer, sizeof(buffer), &myFILE) == NULL) {
		  // Handle end of file or read error
		  LCD_DrawString(0,0, "error", RED);
		  break;
	  }

	  if (currentLine == lineToRead) {
		  // Process the read line
		  // Here, you can print the line, store it in a variable, or perform any desired operations
		  sprintf(question, "%s", buffer);
		  LCD_DrawString(0,100, question, RED);
		  //HAL_Delay(1000);

	  }if (currentLine == lineToRead+1) {
		  // Process the read line
		  // Here, you can print the line, store it in a variable, or perform any desired operations
		  sprintf(answer, "%s", buffer);
		  LCD_DrawString(0,150, answer, BLUE);
		  //HAL_Delay(1000);
		  break;
	  }

	  currentLine++;
  }
  f_close(&myFILE);
  f_mount(&myFATFS," ",0);

}







