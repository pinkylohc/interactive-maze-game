/*
 * game.c
 *
 *  Created on: Apr 12, 2024
 *      Author: pinkylo
 */
#include "game.h"
#include "lcd.h"


uint8_t sequence[5]; // Array to store the random sequence
uint8_t length = 5; // Length of the sequence
uint8_t result[5];	//store the user input result

/*void generate_sequence() {
	uint8_t prev_value = -1;
	bool flag = true;
	for (int i = 0; i < length; i++) {
	    do {
	        sequence[i] = rand() % 3; // Generate random number between 0 and 2
	    } while (sequence[i] == prev_value); // Repeat if the generated number is the same as the previous value
	    prev_value = sequence[i]; // Update the previous value
	}
}*/

void shuffle(uint8_t* array, int len) {
    for (int i = len - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void generate_sequence() {
    uint8_t numbers[] = {0, 1, 2}; // Array containing the numbers 0, 1, 2
    int numbers_length = sizeof(numbers) / sizeof(numbers[0]);

    // Shuffle the numbers array
    shuffle(numbers, numbers_length);
    // Copy the shuffled numbers to the sequence array
    for (int i = 0; i < numbers_length; i++) {
        sequence[i] = numbers[i];
    }
    // Fill the remaining part of the sequence array with random numbers
    for (int i = numbers_length; i < length; i++) {
        sequence[i] = rand() % 3;
    }
    shuffle(sequence, 5);
}


void show_sequence() {
    for (uint8_t i = 0; i < length; i++) {
        if (sequence[i] == 0) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET); // red
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            HAL_Delay(400);

        } else if (sequence[i] == 1) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET); // green
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            HAL_Delay(400);
        } else {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET); // blue
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
            HAL_Delay(400);
        }
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET); // blue
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
        HAL_Delay(400);
    }
}

void user_input() {
	uint8_t len = 0;
    while (len < length) {
         if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == GPIO_PIN_RESET) {
             HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET); // Turn on LED at PB5 //debug
             result[len] = 0;
             len++;
             HAL_Delay(300); // Wait for 500ms
             HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET); // Turn off LED

         }else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) == GPIO_PIN_RESET) {
             HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET); // Turn on LED at PB0  //debug
             result[len] = 1;
             len++;
             HAL_Delay(300); // Wait for 500ms
             HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); // Turn off LED

         }else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET) {
             HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET); // Turn on LED at PB1	//debug
             result[len] = 2;
             len++;
             HAL_Delay(300); // Wait for 500ms
             HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET); // Turn off LED

         }
   }
}


bool check_match(){
    for (int i=0; i<length; i++){
    	if (sequence[i] != result[i]) return false;
    }
    return true;

}

bool light_pattern(){
	generate_sequence();
	show_sequence();
	//LCD_DrawString(0, 120, "please enter your sequence", RED);
	user_input();
	return check_match();
}
