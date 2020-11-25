/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 * https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name : SZE-TO Kwok Leung
 * Student ID : 1155149068
 * Class/Section : D
 * Date : 25-Nov-2020
 */

#include <stdio.h>

/* Macros used to represent the state of each square */
#define EMPTY 0
#define CIRCLE 1
#define CROSS 2

#pragma region Generic
typedef struct s_vector2
{
    int x, y;
} Vector2;

Vector2 newVector2(int x, int y)
{
    Vector2 v = {x, y};
    return v;
}
#pragma endregion

#pragma region Tik - Tac - Toe
/* Initialize the game board by setting all nine squares to EMPTY */
void initGameBoard(int gameBoard[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            gameBoard[i][j] = EMPTY;
        }
    }
}

// Get the number of the squre by the array index.
int getPositionByIndex(int row, int col)
{
    return 3 * row + col + 1;
}

// Get the row index by the squre number.
int getRowByPosition(int num)
{
    // Verify the input
    if (num < 1 || num > 9)
    {
        printf("Invalid square number!");
        return -1;
    }

    return (num - 1) / 3;
}

// Get the column index by the squre number
int getColumnByPosition(int num)
{
    // Verify the input
    if (num < 1 || num > 9)
    {
        printf("Invalid square number!");
        return -1;
    }

    return (num - 1) % 3;
}

// Print the game board
void printGameBoard(int gameBoard[3][3])
{
    printf("=========\n");
    // Start from the last row
    for (int row = 2; row >= 0; row--)
    {
        // Start from the frist col
        for (int col = 0; col < 3; col++)
        {
            if (gameBoard[row][col] == EMPTY)
            {
                // Empty. Print out the number
                printf("|%d|", getPositionByIndex(row, col));
            }
            else if (gameBoard[row][col] == CIRCLE)
            {
                // Circle. Print 'O'
                printf("|O|");
            }
            else if (gameBoard[row][col] == CROSS)
            {
                // CROWW. Print 'X'
                printf("|X|");
            }
        }
        // Next line
        printf("\n");
    }
    printf("=========\n");
}

void placeMarkByHumanPlayer(int gameBoard[3][3], int mark)
{
    int pos = -1, row, col;

    // Get input from the player.
    scanf("%d", &pos);

    row = getRowByPosition(pos);
    col = getColumnByPosition(pos);

    // Mark the game board
    gameBoard[row][col] = mark;
}

/* Return 1 if there is a winner in the game, otherwise return 0 */
/* Note: the winner is the current player indicated in main() */
int hasWinner(int gameBoard[3][3])
{
    // Check Horizontal
    for (int row = 0; row < 3; row++)
    {
        if (gameBoard[row][0] != EMPTY &&
            gameBoard[row][0] == gameBoard[row][1] && gameBoard[row][1] == gameBoard[row][2])
            return 1;
    }

    // Check Vertical
    for (int col = 0; col < 3; col++)
    {
        if (gameBoard[0][col] != EMPTY &&
            gameBoard[0][col] == gameBoard[1][col] && gameBoard[1][col] == gameBoard[2][col])
            return 1;
    }

    // Check Diagonal
    if (gameBoard[1][1] != EMPTY &&
        ((gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2]) ||
         (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0])))
        return 1;

    // If nothing return after all the checkings
    return 0;
}

/* Return 1 if the game board is full, otherwise return 0 */

// Check if the game board is full
int isFull(int gameBoard[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // If there is Empty, the game board is not full
            if (gameBoard[i][j] == EMPTY)
                return 0;
        }
    }

    // No empty => is full
    return 1;
}

// Place the mark in the first empty space by the computer player
void placeMarkByComputerPlayer(int gameBoard[3][3])
{
    printf("Computer places the mark:\n");

    // Loop through the board to find an empty place
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (gameBoard[row][col] == EMPTY)
            {
                gameBoard[row][col] = CROSS;
                return;
            }
        }
    }
}
#pragma endregion

/* The main function */
int main()
{
    /* Local variables */
    int gameBoard[3][3];   // Each element stores 0 (EMPTY), 1 (CIRCLE), or 2 (CROSS)
    int currentPlayer;     // 1: Player 1 (Human)   2: Player 2 (Human) or Computer Player
    int gameEnds;          // 0: The game continues   1: The game ends
    int numOfHumanPlayers; // 1 or 2

    /* Initialize the local variables by invoking a function, using assignment statements, and reading the user input */
    initGameBoard(gameBoard);
    currentPlayer = 1;
    gameEnds = 0;
    printf("How many human players [1-2]?\n");
    scanf("%d", &numOfHumanPlayers); // In Part 1, you can assume that the user input must be valid

    /* Game start
       If there are two human players, they are Player 1 and Player 2
       If there is only one human player, he/she is Player 1 and another player is the computer player
       For both cases, Player 1 moves first and places the CIRCLE mark; while Player 2 (or the computer player) places the CROSS mark
    */

    while (!gameEnds)
    {
        printGameBoard(gameBoard);

        if (currentPlayer == 1)
        {
            // Human
            printf("Player 1, please place your mark [1-9]:\n");
            placeMarkByHumanPlayer(gameBoard, CIRCLE);
        }
        else
        {
            if (numOfHumanPlayers == 1)
            {
                // Computer
                placeMarkByComputerPlayer(gameBoard);
            }
            else
            {
                // Human 2
                printf("Player 2, please place your mark [1-9]:\n");
                placeMarkByHumanPlayer(gameBoard, CROSS);
            }
        }

        // Determine whether the game is ended
        gameEnds = isFull(gameBoard) || hasWinner(gameBoard);

        // Next player
        if (!gameEnds)
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    // End game
    printGameBoard(gameBoard);

    if (hasWinner(gameBoard))
    {
        if (currentPlayer == 1)
        {
            // Human player wins
            printf("Player 1 wins! Congratulations!");
        }
        else
        {
            if (numOfHumanPlayers == 1)
            {
                // Computer wins
                printf("Computer wins!");
            }
            else
            {
                // Player 2 wins
                printf("Player 2 wins! Congratulations!");
            }
        }
    }
    else
    {
        // No one wins => Draw game
        printf("Draw game!");
    }

    printf("\n");

    return 0;
}