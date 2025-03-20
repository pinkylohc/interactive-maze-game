/*
 * maze.c
 *
 *  Created on: Mar 5, 2024
 *      Author: pinkylo
 */

/*
 * function: set the random seed
 */

#include "maze.h"
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "xpt2046.h"

extern uint8_t **maze;	//dynamically allocated array
extern uint8_t rows, columns, start_x, end_x, start_y, end_y, current_x, current_y, next_x, next_y;
extern uint8_t hearts, end, keys, restart_flag, duration;
uint8_t width_margin, height_margin, boundary, base_obs, rcstart, rsize, csize, level;	//easy-1 //medium-2 //diffcult-3
extern const uint8_t block_size;
extern uint8_t Rxstr;
extern UART_HandleTypeDef huart1;

void restart(){
	restart_flag = 0;	//test
	duration = -1;
	keys = 0;
	HAL_Delay(500);
	free_maze_array();
	LCD_Clear (0, 0, 240, 320, WHITE);	// clear the screen
	maze_all();
}


void maze_all(){
	start_page();
	generate_whole_maze();
	LCD_Display();
	duration = 0;
}



void start_page(){
	//start page - touch option
	level = 0;
	LCD_Clear (0, 0, 240, 320, WHITE);
    LCD_DrawString(0, 0, "Discover a treasure under a *flag* in an maze by finding three elusive *keys*. Are you up for the challenge?", BLUE);

    LCD_Clear ( 0, 100, 240, 50, RED );
    LCD_DrawString(110, 120, "easy", 0x03E0);

    LCD_Clear ( 0, 180, 240, 50, GREEN );
    LCD_DrawString(103, 200, "medium", 0x8008);

    LCD_Clear ( 0, 260, 240, 50, YELLOW );
    LCD_DrawString(110, 280, "hard", 0xF800);

    while (level == 0){	//loop until a level is chosen
    	 if ( ucXPT2046_TouchFlag == 1 ){
    		Check_touchkey();
    		ucXPT2046_TouchFlag = 0;
    	 }
    	HAL_Delay(50);
    }

    LCD_Clear (0, 0, 240, 320, WHITE);


    /*LCD_Clear ( 0, 110, 240, 50, BLUE );	//custom
    LCD_DrawString(80, 130, "customisation", RED);

    LCD_Clear ( 0, 220, 240, 50, GREEN );	//random
    LCD_DrawString(70, 240, "random generate", RED);

    while (level == 0){	//loop until a level is chosen 4-custom 5-random
    	if ( ucXPT2046_TouchFlag == 1 ){
    	  Check_touchkey_setup();
    	  ucXPT2046_TouchFlag = 0;
    	 }
    	HAL_Delay(50);
    }
    LCD_Clear (0, 110, 240, 320, WHITE);

    if(level == 5){
		LCD_Clear ( 0, 100, 240, 50, RED );
		LCD_DrawString(110, 120, "easy", 0x03E0);

		LCD_Clear ( 0, 180, 240, 50, GREEN );
		LCD_DrawString(103, 200, "medium", 0x8008);

		LCD_Clear ( 0, 260, 240, 50, YELLOW );
		LCD_DrawString(110, 280, "hard", 0xF800);

		while (level == 5){	//loop until a level is chosen
			 if ( ucXPT2046_TouchFlag == 1 ){
					 Check_touchkey();
					 ucXPT2046_TouchFlag = 0;
			 }
			HAL_Delay(50);
		}
		LCD_Clear (0, 0, 240, 320, WHITE);

    }else if(level == 4){ //heart no., size(col, row), task no.

    	LCD_DrawString(0, 120, "please enter the number of hearts(1-3)", RED);	//no of hearts
    	while(1){	//for number of hearts
    		if(HAL_UART_Receive(&huart1, &Rxstr, 1, 100) == HAL_OK){
    		  	if(Rxstr != '1' && Rxstr != '2' && Rxstr != '3') continue;	//invalid input
    		  	else{ hearts = Rxstr -'0'; break; }
    		}
    	}
    	LCD_DrawString(0, 120, "please enter the row size(odd 9-15)       ", RED);	//row

    	while(1){	//for number of hearts
			if(HAL_UART_Receive(&huart1, &Rxstr, 2, 100) == HAL_OK){
				if(Rxstr != '9' && Rxstr != '11' && Rxstr != "13" && Rxstr != "15") continue;	//invalid input
				else{ rows = Rxstr - '0'; break; }
			}
		}
    	LCD_DrawString(0, 120, "please enter the column size(odd 9-17)            ", RED);	//col
    	while(1){	//for number of hearts
			if(HAL_UART_Receive(&huart1, &Rxstr, 2, 100) == HAL_OK){
				if(Rxstr != '1' && Rxstr != '2' && Rxstr != '3') continue;	//invalid input
				else{ columns = Rxstr -'0'; break; }
			}
		}
    	LCD_DrawString(0, 120, "please enter the number of hearts(1-13)           ", RED);	//no of obstacle
    	while(1){	//for number of hearts
			if(HAL_UART_Receive(&huart1, &Rxstr, 2, 100) == HAL_OK){
				if(Rxstr != '1' && Rxstr != '2' && Rxstr != '3') continue;	//invalid input
				else{ base_obs = Rxstr -'0'; break; }
			}
		}
    }
    LCD_Clear (0, 0, 240, 320, WHITE);*/
}


/*
 * adjust the parameter for different level
 * num_obstacles, hearts, row&col range
 */
void adjust_level(){
	switch(level){

	case 1:	//easy
		hearts = 3;
		base_obs = 4;
		rcstart = 9;
		rsize = 3;
		csize = 3;
		break;

	case 2:	//medium
		hearts = 3;
		base_obs = 7;
		rcstart = 11;
		rsize = 3;
		csize = 3;
		break;

	case 3:	//difficult
		hearts = 2;
		base_obs = 9;
		rcstart = 13;
		rsize = 5;
		csize = 3;
		break;

	default: break; //error
	}
}

void LCD_Display(){	//display

	for (int i = 0; i<keys; i++){	//display key
			  LCD_Drawkey(10, 15+i*32);
	}

	for (int i = 0; i<hearts; i++){	//display heart
	  LCD_Drawheart(10, 130+i*32);
	}

	//draw the maze
	width_margin = (240-columns*block_size)/2;	//decide the start position
	height_margin = (280 - rows*block_size)/2 + 40;
	LCD_maze(maze, width_margin, height_margin, block_size, rows, columns);

}


void generate_whole_maze(){
	//random the row and col, start_x, start_y, end_x, end_y
	  adjust_level();
	  get_random_row_col();
	  get_random_start();

	  // allocatae memory for the maze array (need to do in main)
	  maze = (uint8_t **)malloc(rows * sizeof(uint8_t *));
	  // Allocate memory for the columns of each row
	  for (int i = 0; i < rows; i++) {
		maze[i] = (uint8_t *)malloc(columns * sizeof(uint8_t));
	  }

	  init_maze_array();  // init maze with all wall
	  generate_maze(start_x, start_y);    // have the array with path
	  get_random_end();

	  add_start_end_maze(); //add the start, end position into the array
	  add_key_maze();     // add the three keys in the array
	  add_obstacle_maze();    // add obstacle into array ***

	  current_x = start_x;
	  current_y = start_y;
	  next_x = start_x;
	  next_y = start_y;

}

void setRandomSeed() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long seed = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
    seed ^= getpid();
    seed ^= (uintptr_t)&tv;
    srand(seed);
}

/*
 * set the random height, width for the maze (17,19,21,23)
 */
void get_random_row_col(){
    // get the random row and column size of maze array
    rows = 0;
    columns = 0;
    do {    // for row size
        rows = rcstart + (rand() % rsize);  //random
    } while (rows % 2 == 0);

    do {    // for col size
        columns = rcstart + (rand() % csize);  //random
    } while (columns % 2 == 0);
}


/*
 * randomly set a start position on boundary
 * end point should opposite to the start point
 */
void get_random_start(){
    // get the random value for start and end position
    // start and end - should be in opposite boundary
    boundary = rand() % 4;  // Randomly choose one of the four boundaries
    switch (boundary) {
        case 0:  // Top boundary
            start_x = 1;
            start_y = (rand() % ((columns - 1) / 2)) * 2 + 1;  // odd from 1 to col-2
            break;
        case 1:  // Bottom boundary
            start_x = rows - 2;
            start_y = (rand() % ((columns - 1) / 2)) * 2 + 1;  // odd from1 to col-2
            break;
        case 2:  // Left boundary
            start_x = (rand() % ((rows - 1) / 2)) * 2 + 1;  // odd from 1 to row-2
            start_y = 1;
            break;
        case 3:  // Right boundary
            start_x = (rand() % ((rows - 1) / 2)) * 2 + 1;  // odd from 1 to row-2
            start_y = columns - 2;
            break;
        default:
            break;
    }
}


/*
 * randomly set a end position/opposite to start
 */
void get_random_end(){
    switch (boundary) {
        case 0:  // start in Top boundary
            while(1){
                end_x = rows - 2;
                end_y = rand() % (columns - 2) + 1;    // 1 to col-2
                if(maze[end_x][end_y] == 0){
                    //end_x += 1;
                    break;
                }
            }
            break;
        case 1:  // start in Bottom boundary
            while(1){
                end_x = 1;
                end_y = rand() % (columns - 2) + 1;    // 1 ro col-2
                if(maze[end_x][end_y] == 0){
                    //end_x -= 1;
                    break;
                }
            }
            break;
        case 2:  // start in Left boundary
            while(1){
                end_x = rand() % (rows - 2) + 1;    // 1 to row-2
                end_y = columns - 2;
                if(maze[end_x][end_y] == 0){
                    //end_y += 1;
                    break;
                }
            }
            break;
        case 3:  // Right boundary
            while(1){
                end_x = rand() % (rows - 2) + 1;    // 1 to row-2
                end_y = 1;
                if(maze[end_x][end_y] == 0){
                    //end_x -= 1;
                    break;
                }
            }
            break;
        default:
            break;
    }
}


/*
 * initialise the maze array to all wall
 */
void init_maze_array(){
    // initial the array with all wall
    // wall = 1
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++){
            maze[i][j] = 1;
        }
    }
}

/*
 * free up the memory allocated to maze array
 */
void free_maze_array(){
	//free the dynamically allocated array
	// used when go to next round
    for (int i = 0; i < rows; i++) {
	        if(maze[i] != NULL) free(maze[i]);
	}
    if(maze != NULL) free(maze);
}


/*
 * recursive backtracking algorithm - generate maze with path
 * parameter : start xy position
 */
void generate_maze(uint8_t startx, uint8_t starty) {
	//generate the maze array with 1 as wall and 0 as the empty path
    int directions[4][2] = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};  // Right, Down, Left, Up
    int shuffle[4] = {0, 1, 2, 3};

    // Shuffle the directions randomly
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = shuffle[i];
        shuffle[i] = shuffle[j];
        shuffle[j] = temp;
    }

    // Mark the current cell as empty space
    //printf("%d %d\n", row, col);
    maze[startx][starty] = 0;

    for (int i = 0; i < 4; i++) {
        int dx = directions[shuffle[i]][0];
        int dy = directions[shuffle[i]][1];
        int newRow = startx + dy;  // Neighbor row
        int newCol = starty + dx;  // Neighbor column
        int midRow = startx + dy / 2;  // Midpoint row
        int midCol = starty + dx / 2;  // Midpoint column

        // Check if the neighbor coordinates are within the maze boundaries
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns && maze[newRow][newCol] == 1) {
            // Carve a path between the current cell and the neighbor
            //printf("%d %d\n", midRow, midCol);
            maze[midRow][midCol] = 0;
            generate_maze(newRow, newCol);  // Recursively generate the maze from the neighbor cell
        }
    }
}


/*
 * add the start and end position to the maze
 */
void add_start_end_maze(){
    // add the start, end point to maze array
    maze[start_x][start_y] = 2; // 2 - start positiojn
    maze[end_x][end_y] = 3;     // 3 - end position
}

/*
 * add the three keys to the maze
 */
void add_key_maze(){    //key = 4, three key intotal
    uint8_t num_key = 0;
    while(num_key < 3){
        uint8_t ran_row = rand() % (rows - 2) + 1;
        uint8_t ran_col = rand() % (columns - 2) + 1;
        if(maze[ran_row][ran_col] == 0){
            maze[ran_row][ran_col] = 4;
            num_key++;
        }
    }
}


/*
 * random rearrange a array
 */
void shuffle_array(uint8_t arr[], uint8_t size) {    // randomize the array order
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        uint8_t temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

/*
 * randomly add 8-10 obstacles to the array
 */
void add_obstacle_maze(){    // obstacle - 4 to 9(hardware), 10 - 12(optional software)
    uint8_t obstacle_array[13] = {5,6,7,8,9,10,11,12,13,14,15,16,17}; // list of array
    //uint8_t obstacle_array[13] = {12,12,12,12,12,12,12,12,12,12,12,12,12}; // list of array
    shuffle_array(obstacle_array, 13);  //redorder the array

    // find the random num_obstacles (8-10)
    uint8_t num_obstacles = rand() % 3 + base_obs;

    //for demo use
    //if(level == 3) {num_obstacles = 13; hearts = 5;}

    uint8_t i = 0;
    while(i < num_obstacles){   // randomly place the obstacles
        uint8_t ran_row = rand() % (rows - 2) + 1;
        uint8_t ran_col = rand() % (columns - 2) + 1;
        if(maze[ran_row][ran_col] == 0 && !(maze[ran_row+1][ran_col]>4) &&
        !(maze[ran_row][ran_col+1]>4) && !(maze[ran_row-1][ran_col]>4) && !(maze[ran_row][ran_col-1]>4)){  // avoid two obstacles next to each other
            maze[ran_row][ran_col] = obstacle_array[i];
            i++;
        }
    }
}












