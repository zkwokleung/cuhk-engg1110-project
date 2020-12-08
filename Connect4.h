#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Input.h"
#include "TikTacToe.h"
#include "Genetic.h"

#ifndef Connect4
#define Connect4

#pragma region Connect4
// GameMode: Connect 4
// Since there is no class in C, we added the postfix "C4" to all the related functions.
// In this gamemode, a mark is considered to be a token.
// ***************************************************
// ************** Gameplay Description ***************
// ***************************************************
/*
    A player choose a column to put the token, 
    and the token will fall to the bottom of the column.
    The first player who connected 4 tokens, either vertically, horizontally or diagonally, will win the game.
*/

typedef struct s_gameboardc4
{
    int board[6][7]; // The Game Board. Each column is a pseudo-stack
                     // Index: [row][col]
    int counts[7];   // Counting how many tokens is in each column.
} GameBoard_C4;

GameBoard_C4 new_GameBaord_C4()
{
    GameBoard_C4 gb = {{EMPTY}, {0}};

    return gb;
}

void initGameBaord_C4(GameBoard_C4 *gb)
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

void printGameBoard_C4(GameBoard_C4 *gb)
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
                printf("{O}");
            }
            else if (gb->board[row][col] == CROSS) // Cross. Print 'X'
            {
                printf("{X}");
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
int isColumnFull_C4(GameBoard_C4 *gb, int column)
{
    return gb->counts[column] == 6;
}

// Check if the board is full.
// Return 1 if the board is full, 0 if not
int isFull_C4(GameBoard_C4 *gb)
{
    // Check every column
    for (int i = 0; i < 7; i++)
    {
        if (gb->counts[i] < 6)
            return 0;
    }

    return 1;
}

// Insert a mark into a column of the board
// Return 1 if successfully inserted, return 0 otherwise
int insertToken_C4(GameBoard_C4 *gb, int col, int mark)
{
    // Input validation
    if (col < 0 || col > 6 || isColumnFull_C4(gb, col))
        return 0;

    // Push the mark onto the board and increase the number of marks
    gb->board[gb->counts[col]++][col] = mark;
    return 1;
}

int getInputFromHuman_C4()
{
    printf("Place a token on a column!\n");

    return getNumberInput();
}

int getInputFromComputer_C4(GameBoard_C4 *gb)
{
    int ran;
    do
    {
        // Keep looping if the column is full.
        ran = getRandomInt(7);
    } while (isColumnFull_C4(gb, ran));

    return ran;
}

int getInputFromPlayer_C4(GameBoard_C4 *gb, Player *player)
{
    int ipt = 0;
    if (player->type == Human)
    {
        ipt = getInputFromHuman_C4();
    }
    else
    {
        ipt = getInputFromComputer_C4(gb);
    }

    // Input validation
    if (ipt > 6)
    {
        printf("/// Invalid Input! Please enter the column number between 0 and 6! ///\n");
        ;
        return getInputFromPlayer_C4(gb, player);
    }

    if (isColumnFull_C4(gb, ipt))
    {
        printf("/// The column is full! Please choose another column! ///\n");
        return getInputFromPlayer_C4(gb, player);
    }

    // Input validation passed
    return ipt;
}

/*  Since it is a bit resource-consuming to loop through the entire board everytime, 
    we will only evaluate the spaces around the latest token  */
// When a token is inserted, evaluate if it is a winning move
// Accept the game board and the column where the token was inserted
// Return 1 if it is a winning move, 0 otherwise
int evaluateMove_C4(GameBoard_C4 *gb, int col)
{
    // Evaluate tokens within 4 radius, find if there is 4 same type of token connected
    int count = 0;
    int token = gb->board[gb->counts[col] - 1][col];

    // Check Horizontal
    for (int i = 0; i < 7; i++)
    {
        if (gb->board[gb->counts[col] - 1][i] == token)
        {
            if (++count >= 4)
                return 1;
        }
        else
        {
            count = 0;
        }
    }

    count = 0;

    // Check Vertical
    for (int i = 0; i < 6; i++)
    {
        if (gb->board[i][col] == token)
        {
            if (++count >= 4)
                return 1;
        }
        else
        {
            count = 0;
        }
    }

    count = 0;

    // Check Diagonal
    int height = gb->counts[col] - 1; // Height of the column

    int startCol = col - height; // Which column to start evaluate
    startCol = (startCol < 0) ? 0 : startCol;

    int startRow = height - col; //Which Row to start evaluate
    startRow = (startRow < 0) ? 0 : startRow;

    // slash
    for (int r = startRow, c = startCol; r < 6 && c < 7; r++, c++)
    {
        if (gb->board[r][c] == token)
        {
            if (++count >= 4)
                return 1;
        }
        else
        {
            count = 0;
        }
    }

    count = 0;

    // Backslash
    startCol = col + height;
    startCol = (startCol > 6) ? 6 : startCol;

    startRow = height - (6 - col);
    startRow = (startRow < 0) ? 0 : startRow;

    for (int r = startRow, c = startCol; r < 6 && c >= 0; r++, c--)
    {
        if (gb->board[r][c] == token)
        {
            if (++count >= 4)
                return 1;
        }
        else
        {
            count = 0;
        }
    }

    return 0;
}

// Invoke to start the game loop.
// p2Type: The type of player2. Either Human(0) or Computer(1).
void startConnect4(PlayerType p2Type)
{
    cls();

    // Initialize game board
    GameBoard_C4 _gb = new_GameBaord_C4();
    GameBoard_C4 *gameBoard = &_gb;

    // Initialize players
    Player _p[2] = {newPlayer(0, Human),
                    newPlayer(1, p2Type)};
    Player *player[2] = {&_p[0], &_p[1]};

    int currentTurn = 1; // current turn. 0 => player 1, 1 => player 2
    int gameEnded = 0;   // Is the game over.
    int ipt = 0;         // Input buffer
    int hasWinner = 0;   // 0 if no winner, 1 otherwise

    while (!gameEnded)
    {
        printGameBoard_C4(gameBoard);

        // Switch turn
        currentTurn = (currentTurn == 1) ? 0 : 1;

        // Start turn. Prompt message
        onStartTurn(player[currentTurn]);

        // Input handling. Input validation is done by the function logic
        ipt = getInputFromPlayer_C4(gameBoard, player[currentTurn]);
        insertToken_C4(gameBoard, ipt, player[currentTurn]->mark);

        // Check if the game should end
        hasWinner = evaluateMove_C4(gameBoard, ipt);
        gameEnded = hasWinner || isFull_C4(gameBoard);

        printf("\n\n");
    }

    // winner
    if (hasWinner)
    {
        displayEndGameReport(player[currentTurn]);
    }
    else
    {
        displayEndGameReport(NULL);
    }

    printGameBoard_C4(gameBoard);

    // Pause the program until the player pressed Enter key
    waitForEnterKey();

    // Game Loop ended. Return back to where the function is called
}
#pragma endregion
#endif // !Connect4