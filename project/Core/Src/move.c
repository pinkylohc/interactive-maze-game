/*
 * move.c
 *
 *  Created on: 8 Mar 2024
 *      Author: pinkylo
 */

#include "move.h"
#include "handle.h"
#include <stdio.h>
#include "stm32f1xx_hal.h"

extern uint8_t **maze;	//dynamically allocated array
extern uint8_t current_x, current_y, next_x, next_y, keys, hearts;
extern uint32_t joy[];
extern ADC_HandleTypeDef hadc3;



void move(){
	//just for trial -> replace with touch pad
	//buttom1 - up
	//buttom2 - down
	//buttom3 - left
	//buttom4 - right
	//HAL_ADC_Start_DMA(&hadc3, joy, 2);

	if(hearts == 0) handle_lose();

	/*if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_RESET && HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_RESET){
		move_up();
		HAL_Delay(500);

	}else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_RESET){
		move_down();
		HAL_Delay(500);

	}else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET){
		move_left();
		HAL_Delay(500);

	}else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_RESET){
		move_right();
		HAL_Delay(500);
	}*/

	if (joy[1]>=4000){
		move_up();
		HAL_Delay(300);

	}else if (joy[1]>0 && joy[1]<=800){
		move_down();
		HAL_Delay(300);

	}else if (joy[0]>=4000){
		move_left();
		HAL_Delay(300);

	}else if (joy[0]>0 && joy[0]<=800){
		move_right();
		HAL_Delay(300);
	}
}

void move_up(){
	next_x = current_x - 1;
	next_y = current_y;
	handle_move();
}


void move_down(){
	next_x = current_x + 1;
	next_y = current_y;
	handle_move();
}


void move_left(){
	next_y = current_y - 1;
	next_x = current_x;
	handle_move();
}


void move_right(){
	next_y = current_y + 1;
	next_x = current_x;
	handle_move();
}

void handle_move(){
	int valid = check_valid();
	if (valid == 1){	//handle each movement case
		switch(maze[next_x][next_y]){

		case 0:	//empty
			handle_empty(); break;
		case 3:
			handle_endpt(); break;
		case 4:
			handle_key(); break;
		case 5:
			handle_game1(); break;	//light pattern
		case 6:
			handle_game2(); break;
		case 7:
			handle_game3(); break;
		case 8:
			handle_dark(); break;
		case 9:
			handle_bright(); break;
		case 10:
			handle_ice(); break;
		case 11:
			handle_fire(); break;
		case 12:
			handle_ghost(); break;
		case 13:
			handle_stone(); break;
		case 14:
			handle_door(); break;
		case 15:
			handle_addheart(); break;
		case 16:
			handle_prison(); break;
		case 17:
			handle_hidden(); break;
		default: break;


		}

	}else return;	// no moving action for non valid move
}

int check_valid(){	// check if valid movement
	if (maze[next_x][next_y] == 1)  return 0;	//move to wall
	//if (maze[next_x][next_y] == 3 && keys != 3) return 0;	//go to end point without all keys
	else return 1;
}

