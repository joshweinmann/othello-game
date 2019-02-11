//***************************************************
// Filename: main.c
//
// Author: Nandigam
//***************************************************

#include "othello.h"

// function prototypes
bool isCmdLineArgsValid(int argc, char *argv[]);
bool isInteger(const char *s);

// main driver of the game
int main(int argc, char *argv[])
{
	// exit if command-line arguments are not valid
	if (!isCmdLineArgsValid(argc,argv)) {
		exit(EXIT_FAILURE);
	}

	char board[SIZE][SIZE];
	initializeBoard(board);

	int turn = atoi(argv[1]);		// player to start the game
	char disc = toupper(*argv[2]);	// disc color selected by start player

	char p1Disc, p2Disc;
	if (turn == 1) {
		p1Disc = disc;
		p2Disc = disc == WHITE ? BLACK : WHITE;
	} else {
		p2Disc = disc;
		p1Disc = disc == WHITE ? BLACK : WHITE;
	}

	printf("<<<<< Welcome to the game of Othello >>>>>\n");
	printf("Player 1: %c   Player 2: %c\n", p1Disc, p2Disc);
	printf("Player %d starts the game...\n", turn);
	
	int row, col;

	while (!isGameOver(board)) {
		displayBoard(board);

		if (!isValidMoveAvailable(board,(turn == 1 ? p1Disc : p2Disc))) {
			printf("No valid moves available for player %d. You lose your turn.\n",turn);
		} else {
			do {
				printf("Turn> Player %d(%c) - Enter location to place your disc (row col): ",
							turn, (turn == 1 ? p1Disc : p2Disc));
				scanf("%d %d", &row, &col);
				if (row < 1 || row > SIZE || col < 1 || col > SIZE) {
					printf("Sorry, invalid input. Try again.\n");
					continue;
				}
				row--;	// adjust it for zero-indexed array of board
				col--;  // adjust it for zero-indexed array of board
				if (!isValidMove(board,row,col,(turn == 1 ? p1Disc : p2Disc))) {
					printf("Sorry, that is not a valid move. Try again.\n");
					continue;
				}
				break;
			} while (true);
			placeDiscAt(board,row,col,(turn == 1 ? p1Disc : p2Disc));
		}

		turn = turn == 1 ? 2 : 1;
	}

	char winner = checkWinner(board);
	if (winner == BLACK || winner == WHITE) {
		printf("Game is over. The winner is Player %d.\n", (winner == p1Disc ? 1 : 2));
	} else {
		printf("Game is over. No winner.");
	}

	return EXIT_SUCCESS;
}

bool isCmdLineArgsValid(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Wrong number of arguments to program.\n");
		printf("Usage: ./main startplayer startplayer-disccolor\n");
		printf("Example: ./main 1 B\n");
		return false;
	}

	if (!isInteger(argv[1])) {
		printf("Start player is not an integer.\n");
		printf("Usage: ./main startplayer startplayer-disccolor\n");
		return false;
	}

	int player = atoi(argv[1]);
	if (player < 1 || player > 2) {
		printf("Player number must be 1 or 2.\n");
		printf("Usage: ./main startplayer startplayer-disccolor\n");
		return false;
	}

	char *disc = argv[2];
	if (strlen(disc) > 1 || (*disc != 'B' && *disc != 'b' &&
			*disc != 'W' && *disc != 'w')) {
		printf("Wrong value for the disc color.\n");
		printf("Usage: ./main startplayer startplayer-disccolor\n");
		return false;
	}

	return true;
}

bool isInteger(const char *s)
{
	// ignore any leading whitespace
	while (isspace(*s)) {
		s++;
	}

	// ok if negative integer
	if (*s == '-') {
		s++;
	}

	// ok if digit(s)
	while (isdigit(*s)) {
		s++;
	}

	// ignore any trailing whitespace
	while (isspace(*s)) {
		s++;
	}

	// any character other than '\0' is not an integer
	return *s == '\0' ? true : false;
}

