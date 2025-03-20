/*
 * maze.h
 *
 *  Created on: Mar 5, 2024
 *      Author: pinkylo
 */

#ifndef INC_MAZE_H_
#define INC_MAZE_H_


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"


void maze_all();
void restart();
void adjust_level();
void generate_whole_maze();
void LCD_Display();
void start_page();
void setRandomSeed();
void get_random_row_col();
void get_random_start();
void get_random_end();
void init_maze_array();
void free_maze_array();
void generate_maze(uint8_t startx, uint8_t starty);
void add_start_end_maze();
void add_key_maze();
void shuffle_array(uint8_t arr[], uint8_t size);
void add_obstacle_maze();

#endif /* INC_MAZE_H_ */
