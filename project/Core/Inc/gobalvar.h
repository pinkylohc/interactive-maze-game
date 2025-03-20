/*
 * gobalvar.h
 *
 *  Created on: Mar 7, 2024
 *      Author: pinkylo
 */

#ifndef INC_GOBALVAR_H_
#define INC_GOBALVAR_H_

 //*** start_x, start_y. rows, columns -> need to be odd(for generate_maze algo)***
 uint8_t **maze;	//dynamically allocated array
 uint8_t rows, columns, start_x, end_x, start_y, end_y, current_x, current_y, next_x, next_y;
 uint8_t hearts = 3;
 uint8_t keys = 3;
 uint8_t end = 0; // 0 - not end //1 - win //2 - lose


#endif /* INC_GOBALVAR_H_ */
