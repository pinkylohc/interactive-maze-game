/*
 * handle.c
 *
 *  Created on: Mar 8, 2024
 *      Author: pinkylo
 */

#include "handle.h"
#include "wav.h"
#include "max7219.h"
#include "hm10.h"
#include <string.h>
#include "distance.h"

extern uint8_t **maze;	//dynamically allocated array
extern uint8_t rows, columns, current_x, current_y, next_x, next_y, keys, hearts, end;
extern uint8_t width_margin, height_margin, restart_flag;	//maze_base_x	//maze_base_y = 60	//block_size = 11
extern const uint8_t block_size;
extern volatile int timer;
extern uint8_t start[], endpt[];
uint8_t boo_flag = 0;
extern ADC_HandleTypeDef hadc1;
uint8_t status = 0; //0 - win, 1 - lose
extern char answer[100];
extern UART_HandleTypeDef huart1;
char rxString[100] = {0};

void update_display(){
	//if maze == 32-> special case (reach end without 3 keys)
	//if maze == 20??? (hearts region but max hearts)

	LCD_Clear (width_margin+current_y*block_size, height_margin+current_x*block_size, block_size, block_size, WHITE);	//clear the previous (current xy)
	LCD_Drawelement(height_margin+next_x*block_size, width_margin+next_y*block_size, start, RED);
	if (boo_flag == 1){
		boo_flag = 0;
		LCD_Drawelement(height_margin+current_x*block_size, width_margin+current_y*block_size, endpt, 0xFD20);
		maze[current_x][current_y] = 3;
	}

}

void handle_lose(){
	// end page
	status = 1;
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	LCD_DrawString(100, 100, "you lose!", BLUE);
	game_record();
	LCD_DrawString(100, 200, "next round", RED);
	while(restart_flag == 0) Check_touchkey_start();
	restart();
}

void handle_empty(){	// empty - only need to change the display
	maze[next_x][next_y] = 2;
	maze[current_x][current_y] = 0;
	update_display(); 	//update maze display
	current_x = next_x;
	current_y = next_y;
}


void handle_endpt(){
	if(keys == 3){
		//handle end condition
		// end page
		maze[next_x][next_y] = 2;
	    maze[current_x][current_y] = 0;
		update_display();

		LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
		LCD_DrawString(100, 100, "you win!", BLUE);
		game_record();
		LCD_DrawString(100, 200, "next round", RED);
		while(restart_flag == 0) Check_touchkey_start();
		restart();

	}else{	//reach end without 3 keys
		//handle maze display
		maze[next_x][next_y] = 2;
		maze[current_x][current_y] = 0;
		update_display();
		current_x = next_x;
		current_y = next_y;
		boo_flag = 1;
	}

}


void handle_key(){
	LCD_Drawkey(10, 15+keys*32); //display the key
	keys++;
	//LCD_DrawBox(130+(hearts-1)*32, 10, WHITE, 32);
	//hearts--;
	maze[next_x][next_y] = 2;
	maze[current_x][current_y] = 0;
	update_display();
	current_x = next_x;
	current_y = next_y;


}


void handle_game1(){
	maze[next_x][next_y] = 2;
	maze[current_x][current_y] = 0;
	update_display(); //update maze display
	uint8_t start_flag = 0;
	//char str[10];

	//print instruction
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	LCD_DrawString(0, 0, "light pattern game, please follow the pattern on the LED under the board and tap the corresponding color buttons", BLUE);
	LCD_DrawString(0, 50, "Press start to start the task, wait until the timer start", RED);

	LCD_DrawString(100, 200, "start", RED);
	while(start_flag == 0) start_flag = Check_touchkey_flag(95, 145, 200, 230);
	LCD_DrawString(100, 200, "     ", WHITE);

	bool game1 = light_pattern();	//check timer?
	if (game1 == false){
		hearts--;
		play_audio("LOSE.WAV");
	}else play_audio("WIN.WAV");

	//print maze
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	LCD_Display();
	current_x = next_x;
	current_y = next_y;
}


void handle_game2(){
	/*maze[next_x][next_y] = 2;
		maze[current_x][current_y] = 0;
		//update maze display
			update_display();
			uint8_t start_flag = 0;
			uint8_t sequence_length_clap = 2;
			uint8_t sequence_clap[sequence_length_clap];

			LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
			LCD_DrawString(0, 0, "clap,please follow the LED and clap", BLUE);
			LCD_DrawString(0, 50, "Press start to start the task, wait until the timer start", RED);

			LCD_DrawString(100, 200, "start", RED);
			while(start_flag == 0) start_flag = Check_touchkey_flag(95, 145, 200, 230);
			LCD_DrawString(100, 200, "     ", WHITE);

			uint8_t game_count = 0;

			while (game_count < 4) {
		      if (play_game(sequence_clap, sequence_length_clap)) {
		          game_count++;
		      } else {
		          break;
		      }
		  }

		  if (game_count == 4) {
		      //return true; // User completed 5 games correctly
			  play_audio("WIN.WAV");
		  } else {
		      hearts--; // User made a mistake, game over
		      play_audio("LOSE.WAV");
		  }


		 //print maze
		LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
		LCD_Display();
		current_x = next_x;
		current_y = next_y;*/


		maze[next_x][next_y] = 2;
				maze[current_x][current_y] = 0;

				//update maze display
				update_display();

				current_x = next_x;
				current_y = next_y;
}


void handle_game3(){
	maze[next_x][next_y] = 2;
		maze[current_x][current_y] = 0;
		update_display(); //update maze display
		uint8_t start_flag = 0;

		//print instruction
		LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
		LCD_DrawString(0, 0, "distance game! try to put things in the distance that shown on the screen", BLUE);
		LCD_DrawString(0, 50, "Press start to start the task, wait until the timer start", RED);

		LCD_DrawString(100, 200, "start", RED);
		while(start_flag == 0) start_flag = Check_touchkey_flag(95, 145, 200, 230);
		LCD_DrawString(100, 200, "     ", WHITE);

		//timer = 10;

		bool distance = game_Distance();	//check timer?
		if (distance == false){
			hearts--;
			play_audio("LOSE.WAV");
		}else play_audio("WIN.WAV");

		//timer = -1;	//clean the dot matrix
		//max7219_Clean();
		//print maze
		LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
		LCD_Display();
		current_x = next_x;
		current_y = next_y;
}


void handle_dark(){
	maze[next_x][next_y] = 2;
	maze[current_x][current_y] = 0;
	update_display(); //update maze display
	uint8_t start_flag = 0;
	char str[10];

	//print instruction
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	LCD_DrawString(0, 0, "oops, something is watching you, please decrease the light to avoid their sight.", BLUE);
	LCD_DrawString(0, 50, "Press start to start the task, wait until the timer start", RED);

	LCD_DrawString(100, 200, "start", RED);
	while(start_flag == 0) start_flag = Check_touchkey_flag(95, 145, 200, 220);

	//start the task
	//LCD_Clear (100, 200, 100, 20, WHITE);	// clear the screen
	LCD_DrawString(100, 200, "       ", RED);
	LCD_DrawString(100, 250, "give up", RED);
	//timer = 10;
	//get initial LDR value
	HAL_ADC_Start(&hadc1);	//init the adc
	HAL_ADC_PollForConversion(&hadc1, 1000);	//time need for conversion
	int init_data = HAL_ADC_GetValue(&hadc1);
	int data1 = init_data;
	sprintf(str, "LDR %d  ",init_data);
	LCD_DrawString(100, 150, str, RED);
	timer = 10;
	//print_digit(timer);

	while (true){

		//handle LDR
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 1000);	//time need for conversion
		data1 = HAL_ADC_GetValue(&hadc1);
		sprintf(str, "LDR %d  ", data1);
		LCD_DrawString(100, 150, str, RED);
    	if((init_data - data1) > 300 || data1 < 500) {play_audio("WIN.WAV"); break;}	//dynamic & abs threshold check //task success

    	//give up flag
    	if(Check_touchkey_flag(95, 145, 250, 300)){hearts--; play_audio("LOSE.WAV"); break;}

		if(timer == 0){//task failure
			hearts--;
			play_audio("LOSE.WAV");
			break;
		}
	}
	timer = -1;	//clean the dot matrix
	max7219_Clean();
	//print maze
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	LCD_Display();
	current_x = next_x;
	current_y = next_y;
}


void handle_bright(){
	maze[next_x][next_y] = 2;
	maze[current_x][current_y] = 0;
	update_display(); //update maze display
	uint8_t start_flag = 0;
	char str[10];

	//print instruction
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	LCD_DrawString(0, 0, "Oh, you entered a dark region, you need some light to find the path!", BLUE);
	LCD_DrawString(0, 50, "Press start to start the task, wait until the timer start", RED);

	LCD_DrawString(100, 200, "start", RED);
	while(start_flag == 0) start_flag = Check_touchkey_flag(95, 145, 200, 230);

	//start the task
	//LCD_Clear (100, 200, 100, 20, WHITE);	// clear the screen
	LCD_DrawString(100, 200, "       ", RED);
	LCD_DrawString(100, 250, "give up", RED);
	//timer = 10;
	//get initial LDR value
	HAL_ADC_Start(&hadc1);	//init the adc
	HAL_ADC_PollForConversion(&hadc1, 1000);	//time need for conversion
	int init_data = HAL_ADC_GetValue(&hadc1);
	int data1 = init_data;
	sprintf(str, "LDR %d  ",init_data);
	LCD_DrawString(100, 150, str, RED);
	timer = 10;
	//print_digit(timer);

	while (true){
		//display timer value
		//sprintf(str, "%d  ", timer);
		//LCD_DrawString(100, 100, str, RED);

		//give up flag
		if(Check_touchkey_flag(95, 145, 250, 300)){hearts--; play_audio("LOSE.WAV"); break;}

		//handle LDR
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 1000);	//time need for conversion
		data1 = HAL_ADC_GetValue(&hadc1);
		sprintf(str, "LDR %d  ", data1);
		LCD_DrawString(100, 150, str, RED);
		if((data1 - init_data) > 500 || data1 > 3800) {play_audio("WIN.WAV"); break;}	//dynamic & abs threshold check //task success

		if(timer == 0){
			hearts--;
			play_audio("LOSE.WAV");
			break;
		}	//task failure
	}
	timer = -1;	//clean the dot matrix
	max7219_Clean();

	//print maze
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	LCD_Display();
	current_x = next_x;
	current_y = next_y;
}


void handle_ice(){	//increase temp
	maze[next_x][next_y] = 2;
	maze[current_x][current_y] = 0;
	update_display(); //update maze display
	uint8_t start_flag = 0;
	char str[20];

	//print instruction
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	LCD_DrawString(0, 0, "a cube of ice is blocking the road, please try to melt it!", BLUE);
	LCD_DrawString(0, 50, "Press start to start the task, wait until the timer start", RED);

	LCD_DrawString(100, 200, "start", RED);
	while(start_flag == 0) start_flag = Check_touchkey_flag(95, 145, 200, 230);

	//start the task
	//LCD_Clear (100, 200, 100, 20, WHITE);	// clear the screen
	LCD_DrawString(100, 200, "       ", RED);
	LCD_DrawString(100, 250, "give up", RED);
	//timer = 15;
	float init_data = temp_value();
	init_data = temp_value();
	//int data1 = init_data;
	//int round = init_data;
	//sprintf(str, "init temp %d ",init_data);
	//LCD_DrawString(100, 150, str, RED);
	float data1, re;
	timer = 15;

	while (true){
		//display timer value
		//sprintf(str, "%d  ", timer);
		//LCD_DrawString(100, 100, str, RED);

		//read new value
		 data1 = temp_value();
		 //round = data1;
		 //sprintf(str, "temp %d ",data1);
		 re = data1 - init_data;
		 //LCD_DrawString(100, 180, str, RED);
		 if (re >= 1 || data1 >= 30) {play_audio("WIN.WAV"); break;}

		 //give up flag
		 if(Check_touchkey_flag(95, 145, 250, 300)){hearts--; play_audio("LOSE.WAV"); break;}

		 if(timer == 0){hearts--; play_audio("LOSE.WAV"); break;}	//task failure
	}

	timer = -1;	//clean the dot matrix
	max7219_Clean();
	//print maze
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	LCD_Display();
	current_x = next_x;
	current_y = next_y;
}


void handle_fire(){	//decrease temperature
	maze[next_x][next_y] = 2;
	maze[current_x][current_y] = 0;
	update_display(); //update maze display
	uint8_t start_flag = 0;
	char str[20];

	//print instruction
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	LCD_DrawString(0, 0, "three suns are shine on you and you are so hot, please try to decrease the surrounding temperature", BLUE);
	LCD_DrawString(0, 80, "Press start to start the task, wait until the timer start", RED);

	LCD_DrawString(100, 200, "start", RED);
	while(start_flag == 0) start_flag = Check_touchkey_flag(95, 145, 200, 230);

	//start the task
	//LCD_Clear (100, 200, 100, 20, WHITE);	// clear the screen
	LCD_DrawString(100, 250, "give up", RED);
	LCD_DrawString(100, 200, "       ", RED);
	//timer = 15;
	float init_data = temp_value();
	init_data = temp_value();
	//int data1 = init_data;
	//int round = init_data;
	//sprintf(str, "init temp %d ",init_data);
	//LCD_DrawString(100, 150, str, RED);
	float data1, re;
	timer = 15;

	while (true){
		//display timer value
		//sprintf(str, "%d  ", timer);
		//LCD_DrawString(100, 120, str, RED);
		//print_digit(timer);

		//read new value
		 data1 = temp_value();
		 //round = data1;
		 //sprintf(str, "temp %d ",data1);
		 //LCD_DrawString(100, 180, str, RED);
		 re = init_data - data1;
		 if (re >= 0.25  || data1 <=23) { play_audio("WIN.WAV"); break;}

		 //give up flag
		 if(Check_touchkey_flag(95, 145, 250, 300)){hearts--; play_audio("LOSE.WAV"); break;}

		 if(timer == 0){hearts--; play_audio("LOSE.WAV"); break;}	//task failure
	}

	timer = -1;	//clean the dot matrix
	max7219_Clean();

	//print maze
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	LCD_Display();
	current_x = next_x;
	current_y = next_y;
}


void handle_ghost(){	//quiz zone (replace ghost)
	maze[next_x][next_y] = 2;
	maze[current_x][current_y] = 0;
	update_display(); //update maze display
	uint8_t start_flag = 0;

	//print instruction
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	LCD_DrawString(0, 0, "QUIZ TIME! please answer question with your phone (lowercase/number only)", BLUE);
	LCD_DrawString(0, 50, "Press start to start the task, wait until the timer start", RED);

	LCD_DrawString(100, 200, "start", RED);
	while(start_flag == 0) start_flag = Check_touchkey_flag(95, 145, 200, 230);

	//start the task
	LCD_DrawString(100, 200, "       ", RED);
	LCD_DrawString(100, 250, "give up", RED);

	get_question();	//display a random question on LCD
	int len = strlen(answer);
	len--; //take out the \n
	timer = 15;

	while (true){
		//give up flag
		if(Check_touchkey_flag(95, 145, 250, 300)){hearts--; play_audio("LOSE.WAV"); break;}

		if (HAL_UART_Receive(&huart1,(uint8_t*)rxString,len,200)==HAL_OK){

			if (HAL_UART_Receive(&huart1, (uint8_t*)rxString, 1, 100) == HAL_OK) continue;	//check if the input len > ans len
			rxString[len] = '\0';
			if(strncmp(rxString, answer, len) == 0) { play_audio("WIN.WAV"); break;}
			HAL_UART_Receive(&huart1, (uint8_t*)rxString, 100, 100);	//remove remaining char
		}

		if(timer == 0){
			hearts--;
			play_audio("LOSE.WAV");
			break;
		}	//task failure
	}
	timer = -1;	//clean the dot matrix
	max7219_Clean();

	//print maze
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	LCD_Display();
	current_x = next_x;
	current_y = next_y;
}


void handle_stone(){
	maze[next_x][next_y] = 2;
		maze[current_x][current_y] = 0;

		//update maze display
		update_display();

		current_x = next_x;
		current_y = next_y;
}


void handle_door(){
	maze[next_x][next_y] = 2;
		maze[current_x][current_y] = 0;

		//update maze display
		update_display();

		current_x = next_x;
		current_y = next_y;
}


void handle_addheart(){
		if (hearts == 3){
			//display - your heart is full, nothing happen
			maze[next_x][next_y] = 2;
			maze[current_x][current_y] = 0;
			update_display();
			current_x = next_x;
			current_y = next_y;
		}else{
			maze[next_x][next_y] = 2;
			maze[current_x][current_y] = 0;
			update_display();
			LCD_Drawheart(10, 130+hearts*32); //display the key
			hearts++;
			current_x = next_x;
			current_y = next_y;
		}
}


void handle_prison(){ // minus one heart
	maze[next_x][next_y] = 2;
	maze[current_x][current_y] = 0;

	//update maze display
	update_display();
	LCD_DrawBox(130+(hearts-1)*32, 10, WHITE, 32);
	hearts--;

	current_x = next_x;
	current_y = next_y;

}


void handle_hidden(){
	//display, you trap in a hidden area
	//jump to somewhere else
	LCD_Clear (width_margin+next_y*block_size, height_margin+next_x*block_size, block_size, block_size, WHITE);
	maze[next_x][next_y] = 0;
	while(true){
		next_x = rand() % (rows - 2) + 1;
		next_y = rand() % (columns - 2) + 1;
		if(maze[next_x][next_y] == 0){
		   maze[next_x][next_y] = 2;
		   break;
		}
	}
	maze[current_x][current_y] = 0;
	update_display();
	current_x = next_x;
	current_y = next_y;
	//update maze display

}





