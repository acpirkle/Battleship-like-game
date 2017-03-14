/*
 HW4_Pirkle.c
 Andrew Pirkle
 CS3335
 HW 4
 11/2/15
 */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*
 This method sets up the human's game board.
 The method prompts the user for 2 slots to place the ship piece.
 The program should ensure that the slots are consecutive.
 In other words, your ship cannot be placed at slot 2 and at slot 6.
 since the board has only 10 slots, valid slots are in the range of 0 to 9.
 */
void setBoard(int* pntr) {
	int s1, s2;
	do {
		printf("Enter position of first ship slot(0 - 9): ");
		scanf("%d", &s1);
	} while (s1 > 9);
	do {
		printf("Enter position of second ship slot (0 - 9): ");
		scanf("%d", &s2);
	}while(s2 > 9 || abs(s2 - s1) != 1);
	*(pntr + s1) = 1;
	*(pntr + s2) = 1;
}
/*
 Exactly the same as the setBoard method except
 that the position of the computer's ship is set randomly.
 The computer's ship must also be in consecutive slots
 */
void setComputerBoard(int* pntr) {
	int s1, s2, r;
	do {
		r = rand()%10;
		s1 = r;
	} while (s1 > 9);
	do {
		r = rand()%10;
		s2 = r;
	} while (s2 > 9 || abs(s2 - s1) != 1);
	*(pntr + s1) = 1;
	*(pntr + s2) = 1;
}
/*
 This method prints out and displays the boards
 starting with the human side and ending with the computer's.
 */
void printBoards(int* human, int* computer){
	int i;
	printf("Human Board: \n0 1 2 3 4 5 6 7 8 9\n");
				for (i = 0; i < 10; i++) {
					switch (*(human+i)) {
						case 1:
							printf("S ");
							break;
						case 2:
							printf("H ");
							break;
						case 3:
							printf("M ");
							break;
						default:
							printf("* ");
							break;
					}
				}
	printf("\n\nComputer Board: \n0 1 2 3 4 5 6 7 8 9\n");
				for (i = 0; i < 10; i++){
					switch (*(computer+i)) {
						case 1:
							printf("S ");
							break;
						case 2:
							printf("H ");
							break;
						case 3:
							printf("M ");
							break;
						default:
							printf("* ");
							break;
					}
				}
}
/*
 This method runs the game. computer fires at random.
 determine whether hit or miss. print out computer and human boards.
 switch turns letting human pick which slot to fire at. repeat.
 winner is whoever hits both ship slots in the opponents board.
 */
int playGame(int *human, int *computer) {
	// key for arrays: 1 == ship slot, 2 == H, 3 == M, all else == * .
	int r,cTurn,hTurn,cHitCounter,hHitCounter;
	cHitCounter = 0;
	hHitCounter = 0;
	do{
		r = rand();
		r %= 10;
		cTurn = r;
		printf("\n\nComputer guesses %d\n", cTurn);
		if(*(human+cTurn)==1){
			printf("HIT!\n\n");
			*(human+cTurn) = 2;
			cHitCounter++;
			printBoards(human,computer);
			if(cHitCounter == 2){
				return 0;
			}
		}
		else if(*(human+cTurn)==2){
			*(human+cTurn) = 2;
			printBoards(human,computer);
		}
		else {
			printf("MISS!\n\n");
			*(human+cTurn) = 3;
			printBoards(human,computer);
		}
		do{
			printf("\n\nEnter guess: ");
			scanf("%d",&hTurn);
		} while(hTurn > 9);
		if(*(computer+hTurn)==1){
			printf("HIT!\n\n");
			*(computer+hTurn) = 2;
			hHitCounter++;
			printBoards(human,computer);
			if(hHitCounter == 2){
				return 1;
			}
		}
		else if(*(computer+hTurn)==2){
			*(computer+hTurn) = 2;
			printBoards(human,computer);
		}
		else {
			printf("MISS!\n\n");
			*(computer+hTurn) = 3;
			printBoards(human,computer);
		}
	} while(cHitCounter < 2 && hHitCounter < 2);
}
int main() {
	int *human, *computer;
	int array1[] = {0,0,0,0,0,0,0,0,0,0};
	int array2[] = {0,0,0,0,0,0,0,0,0,0};
	human = array1;
	computer = array2;
	srand(time(NULL));
	setBoard(human);
	setComputerBoard(computer);
	int winner = playGame(human, computer);
	if (winner == 0) {
		printf("\nComputer wins!");
		//cout << "Computer wins!" << endl;
	} else {
		printf("\nHuman wins!");
		//cout << "Human wins!" << endl;
	}
	return 0;
}