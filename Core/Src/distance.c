/*
 * distance.c
 *
 *  Created on: Apr 30, 2024
 *      Author: pinkylo
 */

#include "distance.h"
#include "max7219.h"
#include "xpt2046.h"

uint32_t pMillis;
uint32_t Value1 = 0;
uint32_t Value2 = 0;
uint16_t Distance  = 0;  // cm
extern TIM_HandleTypeDef htim2;
//extern volatile int tim;

int compareNumbers_Distance(int guess, int randomNumber) {
    // Compare the guess with the random number
    if (guess == randomNumber) {
        return 1; // Correct guess
    } else {
        return 0; // Incorrect guess
    }
}

void playGuessingGame_Distance(int randomNumber) {
    //char textangle[] = "The random number is: ";
    char angleString[20];
    sprintf(angleString, "target distance: %d", randomNumber);

    //LCD_DrawString(10, 180, textangle, RED);
    LCD_DrawString(10, 180, angleString, RED);
    LCD_DrawString(10,200,  "current distance: ", RED);

    /*while (1) {
    	int userGuess = measureDistance();
        int result = compareNumbers_Distance(userGuess, randomNumber);

        if (result == 1) {
            LCD_DrawChar(60,60, 'Y', RED);	//win
            break; // Exit the loop on correct guess
        } else {
            LCD_DrawChar(60,60, 'N', RED);	//lose

        }
    }*/
}

int measureDistance() {
    int distance = 0;

        HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_SET);  // pull the TRIG pin HIGH
        __HAL_TIM_SET_COUNTER(&htim2, 0);
        while (__HAL_TIM_GET_COUNTER (&htim2) < 10);  // wait for 10 us
        HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);  // pull the TRIG pin low

        pMillis = HAL_GetTick(); // used this to avoid infinite while loop  (for timeout)
        // wait for the echo pin to go high
        while (!(HAL_GPIO_ReadPin (ECHO_PORT, ECHO_PIN)) && pMillis + 10 >  HAL_GetTick());
        Value1 = __HAL_TIM_GET_COUNTER (&htim2);

        pMillis = HAL_GetTick(); // used this to avoid infinite while loop (for timeout)
        // wait for the echo pin to go low
        while ((HAL_GPIO_ReadPin (ECHO_PORT, ECHO_PIN)) && pMillis + 50 > HAL_GetTick());
        Value2 = __HAL_TIM_GET_COUNTER (&htim2);

        distance = (Value2-Value1)* 0.034/2;

        char DDistance[3];
        int rounded = distance;

        sprintf(DDistance, "%d", rounded);

        LCD_DrawString(150,200,  "   ", RED);
        LCD_DrawString(150, 200, DDistance, RED);

        HAL_Delay(100);

      return distance;
}

bool game_Distance() {

	 HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);  // pull the TRIG pin low

	 //srand(time(NULL)); // Set the seed for random number generation

    int randomNumber = rand() % 11 + 10;

    LCD_DrawString(100, 250, "give up", RED);

    //tim = 10;

    while (1) {

    	//if (tim > 0) print_digit(tim);

    	int measuredDistance;

    	playGuessingGame_Distance(randomNumber);

        measuredDistance = measureDistance();

        if (measuredDistance == randomNumber) return true; // Exit the loop on correct measurement

        if(Check_touchkey_flag(95, 145, 250, 300)) return false;

        //if(tim == 0) return false;
    }

    return false;
}
