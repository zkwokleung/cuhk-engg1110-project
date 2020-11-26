#include <stdio.h>

#ifndef TikTacToe
#define TikTacToe
/* Macros used to represent the state of each square */
#define EMPTY 0
#define CIRCLE 1
#define CROSS 2

typedef struct s_position
{
    int row, col;
} Position;

Position newPosition(int row, int col)
{
    Position v = {row, col};
    return v;
}

#pragma region TikTacToe - GameBoard
typedef struct GameBoard
{
    int board[3][3]; // The game board
    int marked;      // how many squares are marked.
} GameBoard;

// Create and return a new Game Board
GameBoard newGameBoard()
{
    GameBoard gb = {{EMPTY}, 0};

    return gb;
}

/* Initialize the game board by setting all nine squares to EMPTY */
void initGameBoard(GameBoard *gameBoard)
{
    // Init the board
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            gameBoard->board[i][j] = EMPTY;
        }
    }

    // Init the fields
    gameBoard->marked = 0;
}

/* Return 1 if the game board is full, otherwise return 0 */
int isFull(GameBoard *gameBoard)
{
    return gameBoard->marked == 9;
}

// Get the mark from the board
int getMark(GameBoard *gameBoard, Position pos)
{
    return gameBoard->board[pos.col][pos.row];
}

// Return true if the specific square is empty
int isMarked(GameBoard *gameBoard, Position pos)
{
    return getMark(gameBoard, pos) == EMPTY;
}

// Get the number of the squre by the array index.
int getNumberByPosition(Position pos)
{
    return 3 * pos.row + pos.col + 1;
}

// Get the position on board by the squre number.
Position getPositionByNumber(int num)
{
    // Verify the input
    if (num < 1 || num > 9)
    {
        printf("Invalid square number!");
        return newPosition(-1, -1);
    }

    return newPosition((num - 1) / 3, (num - 1) % 3);
}

int hasWinner(GameBoard *gameBoard)
{
    // Check Horizontal
    for (int row = 0; row < 3; row++)
    {
        if (gameBoard->board[row][0] != EMPTY &&
            gameBoard->board[row][0] == gameBoard->board[row][1] && gameBoard->board[row][1] == gameBoard->board[row][2])
            return 1;
    }

    // Check Vertical
    for (int col = 0; col < 3; col++)
    {
        if (gameBoard->board[0][col] != EMPTY &&
            gameBoard->board[0][col] == gameBoard->board[1][col] && gameBoard->board[1][col] == gameBoard->board[2][col])
            return 1;
    }

    // Check Diagonal
    if (gameBoard->board[1][1] != EMPTY &&
        ((gameBoard->board[0][0] == gameBoard->board[1][1] && gameBoard->board[1][1] == gameBoard->board[2][2]) ||
         (gameBoard->board[0][2] == gameBoard->board[1][1] && gameBoard->board[1][1] == gameBoard->board[2][0])))
        return 1;

    // If nothing return after all the checkings => no winner
    return 0;
}

// Print the game board
void printGameBoard(GameBoard *gameBoard)
{
    printf("=========\n");
    // Start from the last row
    for (int row = 2; row >= 0; row--)
    {
        // Start from the frist col
        for (int col = 0; col < 3; col++)
        {
            if (gameBoard->board[row][col] == EMPTY) // Empty. Print out the number
            {
                printf("|%d|", getNumberByPosition(newPosition(row, col)));
            }
            else if (gameBoard->board[row][col] == CIRCLE) // Circle. Print 'O'
            {
                printf("|O|");
            }
            else if (gameBoard->board[row][col] == CROSS) // Cross. Print 'X'
            {
                printf("|X|");
            }
        }
        // Next line
        printf("\n");
    }
    printf("=========\n");
}
#pragma endregion

// Base function of placing a mark on a board
void placeMark(GameBoard *gameBoard, Position pos, int mark)
{
    // Mark the game board
    gameBoard->board[pos.row][pos.col] = mark;

    // Increase the count
    gameBoard->marked++;
}
#pragma endregion

// Get and verify the input until a valid input is received
int getInputFromPlayer()
{
    // TODO:
    return 0;
}

void placeMarkByHumanPlayer(GameBoard *gameBoard, int mark)
{
    // Mark the game board
    placeMark(gameBoard, getPositionByNumber(getInputFromPlayer()), mark);
}

#pragma region AI
// Place the mark in the first empty space by the computer player
void placeMarkByComputerPlayer(GameBoard *gameBoard)
{
    printf("Computer places the mark:\n");

    // TODO: Logic
}
#pragma endregion

#endif // !GeneticUtility