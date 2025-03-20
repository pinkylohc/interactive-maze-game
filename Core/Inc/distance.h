/*
 * distance.h
 *
 *  Created on: Apr 30, 2024
 *      Author: pinkylo
 */

#ifndef INC_DISTANCE_H_
#define INC_DISTANCE_H_

#include "lcd.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"
#include <stdbool.h>


#define TRIG_PIN GPIO_PIN_9
#define TRIG_PORT GPIOB
#define ECHO_PIN GPIO_PIN_8
#define ECHO_PORT GPIOB

int compareNumbers_Distance(int guess, int randomNumber);
void playGuessingGame_Distance(int randomNumber);
int measureDistance();
bool game_Distance();


#endif /* INC_DISTANCE_H_ */
