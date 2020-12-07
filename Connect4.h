#include <stdio.h>
#include "Input.h"
#include "TikTacToe.h"
#include "Genetic.h"

#ifndef Connect4
#define Connect4

#pragma region Connect4
// GameMode: Connect 4
// Since there is no class in C, we added the postfix "C4" to all the related functions.
// In this gamemode, a mark is considered to be a coin.
// ***************************************************
// ************** Gameplay Description ***************
// ***************************************************
/*
    A player choose a column to put the coin, 
    and the coin will fall to the bottom of the column.
    The first player who connected 4 coins, either vertically, horizontally or diagonally, will win the game.
*/
typedef struct s_gameboardc4
{
    int board[6][7]; // The Game Board. Each column is a pseudo-stack
                     // Index: [row][col]
    int counts[7];   // Counting how many coins is in each column.
} GameBoardC4;

GameBoardC4 newGameBaordC4()
{
    GameBoardC4 gb = {{EMPTY}, {0}};

    return gb;
}

void initGameBaordC4(GameBoardC4 *gb)
{
    // Init the board
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            gb->board[row][col] = EMPTY;
        }
    }

    // Init the fields
    for (int i = 0; i < 7; i++)
    {
        gb->counts[i] = 0;
    }
}

void printGameBoardC4(GameBoardC4 *gb)
{
    // Print game board
    for (int row = 5; row >= 0; row--)
    {
        printf("||");
        for (int col = 0; col < 7; col++)
        {
            if (gb->board[row][col] == EMPTY) // Empty. Print out an empty space
            {
                printf("{ }");
            }
            else if (gb->board[row][col] == CIRCLE) // Circle. Print 'O'
            {
                printf(" O ");
            }
            else if (gb->board[row][col] == CROSS) // Cross. Print 'X'
            {
                printf(" X ");
            }
        }
        printf("||\n");
    }

    printf("**");
    // print numbering
    for (int i = 0; i < 7; i++)
    {
        printf("[%d]", i);
    }
    printf("**\n");

    printf("=========================\n");
}

// Check if the column is fulled
int isColumnFull(GameBoardC4 *gb, int column)
{
    return gb->counts[column] == 6;
}

// Check if the board is full.
// Return 1 if the board is full, 0 if not
int isFullC4(GameBoardC4 *gb)
{
    // Check every column
    for (int i = 0; i < 7; i++)
    {
        if (gb->counts[i] == EMPTY)
            return 0;
    }

    return 1;
}

// Insert a mark into a column of the board
// Return 1 if successfully inserted, return 0 otherwise
int insertCoin(GameBoardC4 *gb, int col, int mark)
{
    // Input validation
    if (col < 0 || col > 6 || isColumnFull(gb, col))
        return 0;

    // Push the mark onto the board and increase the number of marks
    gb->board[gb->counts[col]++][col] = mark;
    return 1;
}

int getInputFromHumanC4()
{
    printf("Place a coin on a column!");
    return getNumberInput();
}

// When a coin is inserted, evaluate if it is a winning move
// Accept the game board and the column where the coin was inserted
// Return 1 if it is a winning move, 0 otherwise
int evaluateMove(GameBoardC4 *gb, int col)
{
    // Evaluate coins within 4 radius, find if there is 4 same type of coin connected
    int count = 0;
    int *center = &gb->board[gb->counts[col] - 1][col];
    int *pivot;

    // Check Horizontal
    for (int i = 0; i < 7; i++)
    {
        if (gb->board[gb->counts[col] - 1][i] == *center)
        {
            if (++count >= 4)
                return 1;
        }
        else
        {
            count = 0;
        }
    }

    // Check Vertical
    for (int i = 0; i < 6; i++)
    {
        if (gb->board[i][col] == *center)
        {
            if (++count >= 4)
                return 1;
        }
        else
        {
            count = 0;
        }
    }

    // Check Diagonal

    return 0;
}
#pragma endregion
#endif // !Connect4