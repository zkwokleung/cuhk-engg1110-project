#include <stdio.h>
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
// Function prototypes
void startConnect4(PlayerType p2Type);

typedef struct s_gameboardc4
{
    int board[6][7]; // The Game Board. Each column is a pseudo-stack
                     // Index: [row][col]
    int counts[7];   // Counting how many tokens is in each column.
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
int insertToken(GameBoardC4 *gb, int col, int mark)
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
    printf("Place a token on a column!");

    return getNumberInput();
}

int getInputFromComputerC4(GameBoardC4 *gb)
{
    // TODO: implement
    return 0;
}

int getInputFromPlayerC4(GameBoardC4 *gb, Player *player)
{
    int ipt = 0;
    if (player->type == Human)
    {
        ipt = getInputFromHumanC4();
    }
    else
    {
        ipt = getInputFromComputerC4(gb);
    }

    // Input validation
    if (ipt > 6)
    {
        printf("/// Invalid Input! Please enter the column number between 0 and 6! ///\n");
        ;
        return getInputFromPlayerC4(gb, player);
    }

    if (isColumnFull(gb, ipt))
    {
        printf("/// The column is full! Please choose another column! ///\n");
        return getInputFromPlayerC4(gb, player);
    }

    // Input validation passed
    return ipt;
}

// When a token is inserted, evaluate if it is a winning move
// Accept the game board and the column where the token was inserted
// Return 1 if it is a winning move, 0 otherwise
int evaluateMove(GameBoardC4 *gb, int col)
{
    // Evaluate tokens within 4 radius, find if there is 4 same type of token connected
    int count = 0;
    int *center = &gb->board[gb->counts[col] - 1][col];

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
    int startCol = gb->counts[col] - col + 1;
    startCol = (startCol < 0) ? 0 : startCol;
    int startRow = col - gb->counts[col] + 1;
    startRow = (startRow < 0) ? 0 : startRow;

    // slash
    for (int r = startRow, c = startCol; r < 6 && c < 7; r++, c++)
    {
        if (gb->board[r][c] == *center)
        {
            if (++count >= 4)
                return 1;
        }
        else
        {
            count = 0;
        }
    }

    // Backslash
    startCol = col + gb->counts[col] - 1;
    startCol = (startCol > 6) ? 6 : startCol;
    startRow = gb->counts[col] - (6 - col) - 1;
    startRow = (startRow < 0) ? 0 : startRow;

    for (int r = startRow, c = startCol; r < 6 && c >= 0; r++, c--)
    {
        if (gb->board[r][c] == *center)
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

void onStartTurnC4(Player *player)
{
    if (player->type == Human)
    {
        printf("Player %d's turn\n", player->id + 1);
    }
    else
    {
        printf("Computer's turn\n");
    }
}

// Invoke to start the game loop.
// p2Type: The type of player2. Either Human(0) or Computer(1).
void startConnect4(PlayerType p2Type)
{
    cls();

    // Initialize game data
    GameBoardC4 _gb = newGameBaordC4();
    GameBoardC4 *gameBoard = &_gb;

    // Initialize players
    Player _p[2] = {newPlayer(0, Human),
                    newPlayer(1, Computer)};
    Player *player[2] = {&_p[0], &_p[1]};

    int currentTurn = 1; // current turn. 0 => player 1, 1 => player 2
    int gameEnded = 0;

    int ipt = 0;

    while (!gameEnded)
    {
        printGameBoardC4(gameBoard);

        // Switch turn
        currentTurn = (currentTurn == 1) ? 0 : 1;

        onStartTurnC4(player[currentTurn]);

        ipt = getInputFromPlayerC4(gameBoard, player[currentTurn]);
    }
}
#pragma endregion
#endif // !Connect4