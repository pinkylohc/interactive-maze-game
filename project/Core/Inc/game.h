/*
 * game.h
 *
 *  Created on: Apr 12, 2024
 *      Author: pinkylo
 */

#ifndef INC_GAME_H_
#define INC_GAME_H_

#include <stdbool.h>
#include <unistd.h>
#include "stm32f1xx_hal.h"
#include <stdlib.h>
#include "lcd.h"

void shuffle(uint8_t* array, int len);
void generate_sequence();
void show_sequence();
void user_input();
bool check_match();
bool light_pattern();

#endif /* INC_GAME_H_ */
