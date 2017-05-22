#include <stdio.h>
#include "A4.h"
#include "A4Main.h"

int runA4(void){
	struct game game = {
		{{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}},
		0
	};
	bool notQuit = true;
	while (!is_game_won(game) && notQuit){
		add_random_tile(&game);
		render(game);
		if (!is_move_possible(game)){
			printf("You lost! Score: %d\n\n",game.score);
			return 0;
		} else {
			while (1){
				
				char move;
				while (1){
					printf("Please Input a move (w,a,s,d): ");
					move = getchar();
					if (move != '\n'){
						while (getchar() != '\n');
						if (move == 'Q' || move == 'w' || move == 'a' || move == 's' || move == 'd' || move == 'S'|| move == 'L')
							break;
					}
				}
				if (move ==  'w'){
					if (!update(&game, -1, 0)){
						printf("Can't move up\n");
					} else {break;}
				} else if (move == 's'){
					if (!update(&game, 1, 0)){
						printf("Can't move down\n");
					} else {break;}
				} else if (move == 'a'){
					if (!update(&game, 0, -1)){
						printf("Can't move left\n");
					} else {break;}
				} else if (move == 'd'){
					if (!update(&game, 0, 1)){
						printf("Can't move right\n");
					} else {break;}
				} else if (move == 'S'){
					save_board(game);
					printf("Saved Game!\n\n");	
				} else if (move == 'L'){
					game = load_board();
					render(game);
					printf("Loaded Game!\n\n");	
				} else if (move == 'Q'){
					notQuit = false;
					break;
				}
			}
		}
	}
	render(game);
	printf("Yay! you win!\n\n");
	return 0;
}
