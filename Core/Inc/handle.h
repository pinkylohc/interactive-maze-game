/*
 * handle.h
 *
 *  Created on: Mar 8, 2024
 *      Author: pinkylo
 */

#ifndef INC_HANDLE_H_
#define INC_HANDLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"
#include "maze.h"
#include "xpt2046.h"
#include "stm32f1xx_hal.h"
#include "sd_card.h"
#include "game.h"
#include "temp.h"
#include "clap.h"

void update_display();
void handle_empty();
void handle_endpt();
void handle_key();
void handle_game1();
void handle_game2();
void handle_game3();
void handle_dark();
void handle_bright();
void handle_ice();
void handle_fire();
void handle_ghost();
void handle_stone();
void handle_door();
void handle_addheart();
void handle_prison();
void handle_hidden();
void handle_lose();

#endif /* INC_HANDLE_H_ */
