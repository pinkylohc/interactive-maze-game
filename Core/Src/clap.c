/*
 * clap.c
 *
 *  Created on: Apr 18, 2024
 *      Author: pinkylo
 */
#include "clap.h"
#include "stm32f1xx_hal.h"




void generate_sequence_clap(uint8_t* sequence, uint8_t length) {
    uint8_t prev_value = 1; // Initialize the previous value to 1

    for (uint8_t i = 0; i < length; i++) {
        sequence[i] = (prev_value + rand()) % 2; // Generate random number between 0 and 1, excluding consecutive 0s
        prev_value = sequence[i]; // Update the previous value
    }
}


// Show the LED sequence to the user
void show_sequence_clap(const uint8_t* sequence, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        if (sequence[i] == 0) {
        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1); // Turn on LED on GPIOB PIN 12
        	HAL_Delay(500); // Wait for 500ms
        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0); // Turn off LEDs
        } else {
        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1); // Turn on LED on GPIOB PIN 13
        	HAL_Delay(500); // Wait for 500ms
        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0); // Turn off LEDs
        }

        HAL_Delay(200); // Wait for 500ms
    }
}

/*
// Wait for the user to repeat the LED sequence
void wait_for_user_input_clap(const uint8_t* sequence, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        while (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) || HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6)); // Wait until both buttons are released

        while (!HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) && !HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6)); // Wait until one of the buttons is pressed

        if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5)) {
        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1); // Turn on LED on GPIOB PIN 12
        } else {
        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1); // Turn on LED on GPIOB PIN 13
        }

        HAL_Delay(500); // Wait for 500ms

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0); // Turn off LEDs
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0); // Turn off LEDs
        HAL_Delay(500); // Wait for 500ms
    }
}

bool play_game(uint8_t* sequence, uint8_t sequence_length) {
    uint8_t user_input[sequence_length];

    generate_sequence_clap(sequence, sequence_length);
    show_sequence_clap(sequence, sequence_length);

    for (uint8_t i = 0; i < sequence_length; i++) {
        while (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) || HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6)); // Wait until both buttons are released

        while (!HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) && !HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6)); // Wait until one of the buttons is pressed

        if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5)) {
            user_input[i] = 0;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1); // Turn on LED on GPIOB PIN 12
        } else {
            user_input[i] = 1;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1); // Turn on LED on GPIOB PIN 13
        }

        HAL_Delay(500); // Wait for 500ms

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0); // Turn off LEDs
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0); // Turn off LEDs
        HAL_Delay(500); // Wait for 500ms
    }

    for (uint8_t i = 0; i < sequence_length; i++) {
        if (user_input[i] != sequence[i]) {
            return false; // User made a mistake, return false
        }
    }

    return true; // User completed the sequence correctly, return true
}
*/

void wait_for_user_input_clap(uint8_t* user_input, const uint8_t* sequence, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        while (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) || HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6)); // Wait until both buttons are released

        while (!HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) && !HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6)); // Wait until one of the buttons is pressed

        if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5)) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1); // Turn on LED on GPIOB PIN 12
            user_input[i] = 0; // Store user input as 0
        } else {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1); // Turn on LED on GPIOB PIN 13
            user_input[i] = 1; // Store user input as 1
        }

        HAL_Delay(500); // Wait for 500ms

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0); // Turn off LEDs
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0); // Turn off LEDs
        HAL_Delay(500); // Wait for 500ms
    }
}

bool play_game(uint8_t* sequence, uint8_t sequence_length) {
    uint8_t user_input[sequence_length];

    generate_sequence_clap(sequence, sequence_length);
    show_sequence_clap(sequence, sequence_length);

    wait_for_user_input_clap(user_input, sequence, sequence_length);

    for (uint8_t i = 0; i < sequence_length; i++) {
        if (user_input[i] != sequence[i]) {
            return false; // User made a mistake, return false
        }
    }

    return true; // User completed the sequence correctly, return true
}


