#include <stdio.h>
#include "A2.h"

/**
  Dtects whether the game is already solved.
  If there is a minimum number of 3 consectuive 'X' charcters (next to each other)
  in the field, return 1. Return 0 otherwise.
 **/
int is_solved(const int size, char field[][size]){
	int space_count = 0;
	for (int y = 0; y < size; y++){
		int o_count = 0;
		int x_count = 0;
		for (int x = 0; x < size; x++){
			if (field[y][x] == 'x'){
				x_count++;
				o_count = 0;
			} else if (field[y][x] == 'o'){
				o_count++;
				x_count = 0;
			} else {
				space_count++;
				x_count = 0;
				o_count = 0;
			}
			if (x_count >= 3 || o_count >= 3){
				return 1;
			}
		}
	}
	for (int x = 0; x < size; x++){
		int o_count = 0;
		int x_count = 0;
		for (int y = 0; y < size; y++){
			if (field[y][x] == 'x'){
				x_count++;
				o_count = 0;
			} else if (field[y][x] == 'o'){
				o_count++;
				x_count = 0;
			} else {
				space_count++;
				x_count = 0;
				o_count = 0;
			}
			if (x_count >= 3 || o_count >= 3){
				return 1;
			}
		}
	}
	int y_start = size-3;
	int x_start = 0;
	while (y_start >= 0){
		int y = y_start--;
		int x = x_start;
		int o_count = 0;
		int x_count = 0;
		while (y <= size-3 || x <= size-1){
			if (field[y][x] == 'x'){
				x_count++;
				o_count = 0;
			} else if (field[y][x] == 'o'){
				o_count++;
				x_count = 0;
			} else {
				space_count++;
				x_count = 0;
				o_count = 0;
			}
			if (x_count >= 3 || o_count >= 3){
				return 1;
			}
			y++;
			x++;
		}
	}
	y_start = 0;
	x_start = size-3;
	while (x_start >= 0){
		int y = y_start;
		int x = x_start--;
		int o_count = 0;
		int x_count = 0;
		while (y <= size-3 || x <= size-1){
			if (field[y][x] == 'x'){
				x_count++;
				o_count = 0;
			} else if (field[y][x] == 'o'){
				o_count++;
				x_count = 0;
			} else {
				space_count++;
				x_count = 0;
				o_count = 0;
			}
			if (x_count >= 3 || o_count >= 3){
				return 1;
			}
			y++;
			x++;
		}
	}	
	y_start = size-3;
	x_start = size-1;
	while (y_start >= 0){
		int y = y_start--;
		int x = x_start;
		int o_count = 0;
		int x_count = 0;
		while (y <= size-3 || x >= 0){
			if (field[y][x] == 'x'){
				x_count++;
				o_count = 0;
			} else if (field[y][x] == 'o'){
				o_count++;
				x_count = 0;
			} else {
				space_count++;
				x_count = 0;
				o_count = 0;
			}
			if (x_count >= 3 || o_count >= 3){
				return 1;
			}
			y++;
			x--;
		}
	}
	y_start = 0;
	x_start = 2;
	while (x_start <= size-1){
		int y = y_start;
		int x = x_start++;
		int o_count = 0;
		int x_count = 0;
		while (y <= size-1 || x >= 0){
			if (field[y][x] == 'x'){
				x_count++;
				o_count = 0;
			} else if (field[y][x] == 'o'){
				o_count++;
				x_count = 0;
			} else {
				space_count++;
				x_count = 0;
				o_count = 0;
			}
			if (x_count >= 3 || o_count >= 3){
				return 1;
			}
			y++;
			x--;
		}
	}
	if (space_count == 0){
		return 2;
	}
	return 0;
}

/**
  A function which puts an 'X' character at the position selected (entered) by the user.
  If the selected position is already in use the function will return 0. Otherwise
  the function will return 1. If the entered position is outside the field, the funcion will return -1.
 **/
int add_cross(const int size, char field[][size], const int x, const int y, const char player){
	if (x < 1 || x > size || y < 1 || y > size){
		return -1;
	} else if (field[y-1][x-1] == ' '){
		if (player == 'A'){
			field[y-1][x-1] = 'x';
		} else {
			field[y-1][x-1] = 'o';
		}
		return 1;
	} else {
		return 0;
	}

}

/**
  Private draw helper which draws the lines (+ and -) based on size
 **/
void drawLines(const int size){
	printf("  ");
	for (int i = 0; i < size; i++){
		printf("+-");
	}
	printf("+\n");
}

/**
	A function that draws the tictactoe board in a 2D array. 
	 - The rows will be printed from LEFT to RIGHT start wtih 1!
	 - the columns will be printed from BOTTOM to UP start with 1!
 **/
void draw(const int size, char field[][size]){
	printf("\n");
	drawLines(size);
	for (int y = 0; y < size; y++){	
		printf("%d ",y+1);
		for (int x = 0; x < size; x++){
			printf("|%c",field[y][x]);
		}
		printf("|\n");
		drawLines(size);
	}
	printf("  ");		
	for (int x = 1; x <= size; x++){
		printf(" %d", x);
	}
	printf("\n\n");
}


int runA2(void){
	printf("\nEnter the size of field: ");
	int size;
	scanf("%d",&size);
	char field[size][size];
	for (int y = 0; y < size; y++){
		for (int x = 0; x < size; x++){
			field[y][x] = ' ';
		}
	}
	draw(size, field);
	char player = ' ';
	int loop = 0;
	while (loop == 0){
		if (player == 'A'){
			player = 'B';
		} else {
			player = 'A';
		}
		printf("Player %c: ", player);
		int y;
		int x;
		scanf("%d %d", &x, &y);
		int check_move = add_cross(size, field, x, y, player);
		if (check_move == -1){
			printf("Wrong position!\n");
		} else if (check_move == 0){
			printf("x is already there!\n");
		} else {
			draw(size, field);
		}
		loop = is_solved(size, field);
	}
	
	if (loop == 2){
		printf("It's a draw!\n\n");
	} else {
		printf("Player %c won!\n\n", player);	
	}
	return 0;
}
