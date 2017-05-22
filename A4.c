#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "A4.h"


#define HEIGHT 4
#define WIDTH 4
#define WIN_CHAR 'K'
#define LINE_HOR "---+"
#define LINE_VERT "|"
#define FILE_NAME "file.txt"

void add_random_tile(struct game *game){
	int row, col;

	// find random, but empty tile
	do{
		col = rand() % 4;
		row = rand() % 4;
	}while(game->board[row][col] != ' ');

	// place to the random position 'A' or 'B' tile
	int tile = 'A' + (rand() % 2);
	game->board[row][col] = tile;
	//Adds to score	
}


/**
 * Helper method, prints lines based on WIDTH value
 **/
void render_lines(){
	printf("+");
	for (int i = 0; i < WIDTH; i++){
		printf(LINE_HOR);
	}
	printf("\n");

}

void render(const struct game game){
	system("cls");
	system("clear");
	printf("\n");
	for (int index_y = 0; index_y < HEIGHT; index_y++){
		render_lines();
		for (int index_x = 0; index_x < WIDTH; index_x++){
			printf("%s %c ",LINE_VERT, game.board[index_y][index_x]);
		}
		printf("|\n");
	}
	render_lines();
}


/*
* Game logic for shifting charcters up or down (for a certain x value)
*/
bool shiftY(char board[WIDTH][HEIGHT], int end_y, int change, int x, int *score){
	bool to_return = false;
	for (int y = end_y+change; y < HEIGHT && y >= 0; y += change){	
		if (board[y][x] != ' ' && board[end_y][x] == ' '){
			to_return = true;
			board[end_y][x] = board[y][x];
			board[y][x] = ' ';
		} else if (board[y][x] == ' '){ 
			continue;
		} else if (board[y][x] == board[end_y][x]){
			to_return = true;
			int score_exp = 'A' - board[end_y][x] + 1;
			*score += pow(2,score_exp);
			board[end_y][x]++;
			board[y][x] = ' ';
			end_y += change;
		} else if (end_y+change != y){
			to_return = true;
			board[end_y+change][x] = board[y][x];
			board[y][x] = ' ';
			end_y += change;
		} else {
			end_y += change;
		}
	}
	return to_return;
}

/*
* Game logic for shifting charcters left or right (for a certain y value)
*/
bool shiftX(char board[WIDTH][HEIGHT], int end_x, int change, int y, int *score){
	bool to_return = false;
	for (int x = end_x+change; x < WIDTH && x >= 0; x += change){
		if (board[y][x] != ' ' && board[y][end_x] == ' '){
			to_return = true;
			board[y][end_x] = board[y][x];
			board[y][x] = ' ';
		} else if (board[y][x] == ' '){ 
			continue;
		} else if (board[y][x] == board[y][end_x]){
			to_return = true;		
			int score_exp = 'A' - board[y][end_x] + 1;
			*score += pow(2,score_exp);
			board[y][end_x]++;
			board[y][x] = ' ';
			end_x += change;
		} else if (end_x+change != x){
			to_return = true;
			board[y][end_x+change] = board[y][x];
			board[y][x] = ' ';
			end_x += change;
		} else {
			end_x += change;
		}
	}
	return to_return;
}

bool update(struct game *game, int dy, int dx){
	int index_change;
	int end_index;
	if (dy == 1 && dx == 0){
		end_index = HEIGHT-1;
		index_change = -1;
	} else if (dy == -1 && dx == 0){
		end_index = 0;
		index_change = 1;
	} else if (dx == -1 && dy == 0){
		end_index = 0;
		index_change = 1;
	} else if (dx == 1 && dy == 0){
		end_index = WIDTH-1;
		index_change = -1;
	} else {
		return false;
	}
	bool to_return = false;
	if (dy != 0){
		for (int x = 0; x < WIDTH; x++){
			if (shiftY(game->board, end_index, index_change, x, &(game->score)))
				to_return = true;
		}
	} else {
		for (int y = 0; y < HEIGHT; y++){
			if (shiftX(game->board, end_index, index_change, y, &(game->score)))
				to_return = true;
		}
	}
	return to_return;
}


bool is_game_won(const struct game game){
	//checks every character in board for K
	for (int index_x = 0; index_x < WIDTH; index_x++){
		for (int index_y = 0; index_y < HEIGHT; index_y++){
			if (game.board[index_y][index_x] == WIN_CHAR){
				return true;
			}
		}
	}
	//There is no K
	return false;
}

bool is_move_possible(const struct game game){
	//checks every character
	for (int index_x = 0; index_x < WIDTH; index_x++){
		for (int index_y = 0; index_y < HEIGHT; index_y++){
			//empty space
			if (game.board[index_y][index_x] == ' '){
				return true;
			}
			//horizontal check
			if (index_x < WIDTH-1 && game.board[index_y][index_x] == game.board[index_y][index_x+1]){
				return true;
			}
			//vertical check
			if (index_y < HEIGHT-1 && game.board[index_y][index_x] == game.board[index_y+1][index_x]){
				return true;
			}
		}
	}
	return false;
}

void save_board(struct game game){
	FILE *in;
	if ((in = fopen(FILE_NAME, "w")) == NULL){
		printf("Error opening file\n");
		exit(1);
	} else {
		for (int y=0; y < HEIGHT; y++){
			for (int x = 0; x < WIDTH; x++){
				fprintf(in,"%c",game.board[y][x]);
			}	
		}
		fprintf(in,"%d ",game.score);
		fclose(in);
	}
}

struct game load_board(){
	FILE *out;
	
	if ((out = fopen(FILE_NAME, "r")) == NULL){
		printf("Error opening file\n");
		exit(1);
	} else {
		struct game game = {
				{{' ',' ',' ',' '},
				{' ',' ',' ',' '},
				{' ',' ',' ',' '},
				{' ',' ',' ',' '}},
				0};
		for (int y=0; y < HEIGHT; y++){
			for (int x = 0; x < WIDTH; x++){
				fscanf(out,"%c",&(game.board[y][x]));
			}
		}
		fscanf(out,"%d",&(game.score));
		fclose(out);
		return game;
	}
}
