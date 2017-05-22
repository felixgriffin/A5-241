#include <stdio.h>
#include <stdlib.h>
#include "A4Main.h"
#include "A2.h"
#include "A1.h"


void printGames(int size, char *games[size], int index){	
	//clears terminal
	//system("cls"); // windows
	system("clear"); // unix

	printf("\n");
	for (int i = 0; i < size; i++){
		if (i == index){	
			printf(" > ");
			printf(games[i]);	
			printf("\n");
		}else{
			printf("   ");
			printf(games[i]);
			printf("\n");
		}
	}
	printf("\n");
}

int main(void){
	char *games[3] = {"K", "TicTacToe", "GuessTheNumber"};
	//runA4()
	int index = 0;
	while(1){
		printGames(3, games, index);
		char move = ' ';
		while (1){
			printf("Please Input a move (w,a,s,d): ");
			move = getchar();		
			if (move != '\n'){
				while (getchar() != '\n');
			}
			if (move == 'Q' || move == 'w' || move == 's' || '\n')
				break;
		}
		if (move == 'w' && index > 0)
			index -= 1;
		if (move == 's' && index < 2)
			index += 1;
		if (move == 'Q')
			break;
		if (move == '\n' && index == 0)
			runA4();
		if (move == '\n' && index == 1)
			runA2();
		if (move == '\n' && index == 2)
			runA1();
	}
	printf("BYE BYE!\n\n");
}
