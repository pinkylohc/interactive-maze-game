/*
 * clap.h
 *
 *  Created on: Apr 18, 2024
 *      Author: pinkylo
 */

#ifndef INC_CLAP_H_
#define INC_CLAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

void generate_sequence_clap(uint8_t* sequence, uint8_t length);
void show_sequence_clap(const uint8_t* sequence, uint8_t length);
void wait_for_user_input_clap(uint8_t* user_input, const uint8_t* sequence, uint8_t length);
bool play_game(uint8_t* sequence, uint8_t sequence_length);


#endif /* INC_CLAP_H_ */
