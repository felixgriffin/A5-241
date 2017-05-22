//Importing all the Necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Defining all the macros
#define START 1
#define END 100
#define ATTEMPTS 5

/***
  A simple helper method which returns a randomly generated number
 ***/
int get_secret(const int start, const int end){
	srand(time(NULL));
	return (rand() % end) + start;
}

/***
  A simple helper method which takes input from the user and returns the input
 ***/
int get_guess(const int attempt){
	int guess;
	printf("Your #%d guess: ", attempt);
	scanf("%d", &guess);
	return guess;
}

/***
  A simple helper method which:
  - compares input with random number
  Tells user that number is the same as input
  Tells user that number is higher/lower otherwise
 ***/
int is_game_won(const int guess, const int randomNumber){
	if (randomNumber > guess)
		printf("Hmm... My number is bigger than yours.\n");
	else if (randomNumber < guess)
		printf("Hmm... My number is smaller than yours.\n");
	else {
		printf("Congratulations! You found it!\n");
		return ATTEMPTS+1;
	}
	return 0;
}


/***
  Task 5: A simple guess the number game
  - chooses random number (using get guess function)
  - Repeats the next steps either 5 times or when input is the same as number
  - Take input (using get_guess method)
  - compare method and input (using is_game_won method)
  - Asks user whether they want to repeat the game
  Y or y means yes
  N or n means no
 ***/
int runA1(void){
	char playAgain = 'y';
	while (playAgain == 'y' || playAgain == 'Y'){
		printf("\nPick a number between %d-%d, You have max. %d attempts.\n", START, END, ATTEMPTS);
		int randomNumber = get_secret(START, END);
		int i;
		for (i = 1; i <= ATTEMPTS; i++){
			i += is_game_won(get_guess(i), randomNumber);
			if (i == 5)printf("\nGame over. My number was %d\n",randomNumber);
			printf("\n");
		}
		while (getchar() != '\n');	
		playAgain = ' ';
		printf("Play again?(y/n): ");
		while (playAgain != 'y' && playAgain != 'Y' && playAgain != 'n' && playAgain != 'N')	
			playAgain = getchar();
	}
	printf("See you later!\n\n");
	return 0;
}
