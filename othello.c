//***************************************************
// Filename: othello.c
//
// Author: Josh Weinmann
//***************************************************

#include "othello.h"

// Displays the board (as SIZE x SIZE grid) on console
void displayBoard(char board[][SIZE])
{
	printf("\n");
	for (int i = 0; i < SIZE; i++) {
		printf((i == 0 ? "%5d" : "%3d"), i+1);
	}
	printf("\n");

	for (int i = 0; i < SIZE; i++) {
		printf("%2d", i+1);
		for (int j = 0; j < SIZE; j++) {
			printf("%3c", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// Initializes the board with start configuration of discs (see project specs)
void initializeBoard(char board[][SIZE])
{
	// fill spots with -
	for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
			board[i][j] = '-';
		}
	}

	// put in starting pieces
	board[3][3] = BLACK;
        board[3][4] = WHITE;
        board[4][3] = WHITE;
        board[4][4] = BLACK;
}

// Returns true if moving the disc to location row,col is valid; else returns false
bool isValidMove(char board[][SIZE], int row, int col, char disc)
{
	// check if space occupied 
	if (board[row][col] != '-') {
		return false;
	}

	



	return true;	// REPLACE THIS WITH YOUR IMPLEMENTATION
}

// Places the disc at location row,col and flips the opponent discs as needed
void placeDiscAt(char board[][SIZE], int row, int col, char disc)
{
	// place disc
	board[row][col] = disc;

	int right;

	// check for rightmost disc
	for (int i = col; i < SIZE; i++) {
		if (board[row][i] == disc) {
			right = i;
		}
	}

	int left; 

	// check for leftmost disc
        for (int i = col; i >= 0; i--) {
                if (board[row][i] == disc) {
                        left = i;
                }
        }

	int top;

	// check for topmost disc
	for (int i = row; i >= 0; i--) {
		if (board[i][col] == disc) {
			top = i;
		}
	}

	int bottom;

	// check for bottommost disc
	for (int i = row; i < SIZE; i++) {
		if (board[i][col] == disc) {
			bottom = i;
		}
	}

	// top right
	int topRightRow;
	int topRightCol;

	int i = col;
	int j = row;

	// check for top-rightmost diagonal disc
	while (i < SIZE && j >= 0) {
		if (board[i][j] == disc) {
			topRightRow = j;
			topRightCol = i;
                }
		i++;
		j--;
	}

	// top left
	int topLeftRow;
	int topLeftCol;

	i = col;
	i = row;

	// check for top-leftmost diagonal disc
	while (i >= 0 && j >= 0) {
                if (board[i][j] == disc) {
                        topLeftRow = j;
                        topLeftCol = i;
                }
                i--;
                j--;
        }

	// bottom right
	int bottomRightRow;
	int bottomRightCol;

	i = col;
	j = row;

	// check for bottom-rightmost diagonal disc
	while (i < SIZE && j < SIZE) {
                if (board[i][j] == disc) {
                        bottomRightRow = j;
                        bottomRightCol = i;
                }
                i++;
                j++;
        }

	// bottom left
	int bottomLeftRow;
	int bottomLeftCol;

	i = col;
	j = row;

	// check for bottom-leftmost diagonal disc
	while (i >= 0 && j < SIZE) {
                if (board[i][j] == disc) {
                        bottomLeftRow = j;
                        bottomLeftCol = i;
                }
                i--;
                j++;
        }
	
	// change discs to right
	if (right > col) {
		for (int i = right-1; i > col; i--) {
			if (board[row][i] == BLACK || board[row][i] == WHITE) {
				board[row][i] = disc;
			}
		}
	}

	// change discs to left
	if (left < col) {
		for (int i = left+1; i < col; i++) {
			if (board[row][i] == BLACK || board[row][i] == WHITE) {
				board[row][i] = disc;
			}
		}
	}

	// change discs to top
	if (top < row) {
		for (int i = top+1; i < row; i++) {
                        if (board[i][col] == BLACK || board[i][col] == WHITE) {
                                board[i][col] = disc;
                        }
                }
	}

	// change discs to bottom
	if (bottom > row) {
		for (int i = bottom-1; i > row; i--) {
                        if (board[i][col] == BLACK || board[i][col] == WHITE) {
                                board[i][col] = disc;
                        }
                }
	}

	// change discs to top-right
	if (topRightRow < row && topRightCol > col) {
		int i = topRightRow+1;
		int j = topRightCol-1;
		while (i < row && j > col) {
			if (board[i][j] == BLACK || board[i][j] == WHITE) {
				board[i][j] = disc;
			}
			i++;
			j--;
		}
	}

	// change discs to top-left
	if (topLeftRow < row && topLeftCol < col) {
                int i = topLeftRow+1;
                int j = topLeftCol+1;
                while (i < row && j < col) {
                        if (board[i][j] == BLACK || board[i][j] == WHITE) {
                                board[i][j] = disc;
                        }
                        i++;
                        j++;
                }
        }

	// change discs to bottom-right
	if (bottomRightRow > row && bottomRightCol > col) {
                int i = bottomRightRow-1;
                int j = bottomRightCol-1;
                while (i > row && j > col) {
                        if (board[i][j] == BLACK || board[i][j] == WHITE) {
                                board[i][j] = disc;
                        }
                        i--;
                        j--;
                }
        }

	// change discs to bottom-left
	if (bottomLeftRow > row && bottomLeftCol < col) {
                int i = bottomLeftRow-1;
                int j = bottomLeftCol+1;
                while (i > row && j < col) {
                        if (board[i][j] == BLACK || board[i][j] == WHITE) {
                                board[i][j] = disc;
                        }
                        i--;
                        j++;
                }
        }

}

// Returns true if a valid move for disc is available; else returns false
bool isValidMoveAvailable(char board[][SIZE], char disc)
{
	// check all spaces
	for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
			
			// check if move is valid in space
			if (isValidMove(board, i, j, disc)) {
				return true;
			}
		}
	}		

	// no valid moves
	return false;
}

// Returns true if the board is fully occupied with discs; else returns false
bool isBoardFull(char board[][SIZE])
{
	// check all spots for openings
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {

			// check for open spots
			if (board[i][j] == '-') {
				return false;
			}
		}
	}
	return true;
}

// Returns true if either the board is full or a valid move is not available for either disc
bool isGameOver(char board[][SIZE])
{
	// check if board is full
	if (isBoardFull(board)) {
		return true;
	}

	// check if valid move is available for black
	else if (!isValidMoveAvailable(board, BLACK)) {
		return true;
	}

	// check if valid move is available white
        else if (!isValidMoveAvailable(board, WHITE)) {
		return true;
        }

	// game is not over
	return false;
}

// If there is a winner, it returns the disc (BLACK or WHITE) associated with the winner.
// In case of a tie, it returns EMPTY
char checkWinner(char board[][SIZE])
{
	// keep track of disc counts
	int w = 0;
	int b = 0;

	// count player discs
	for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {

                        // check for black discs
                        if (board[i][j] == 'B') {
                        	b++;
			}

			// check for white discs
			if (board[i][j] == 'W') {
                                w++;
                        }
                }
        }

	// more white discs
	if (w > b) {
		return WHITE;
	}

	// more black discs
	else if (b > w) {
		return BLACK;
	}

	// tie
	else {
		return EMPTY;
	}
}
