#include <stdio.h>
#include "Input.h"
#include "Genetic.h"

#ifndef TikTacToe
#define TikTacToe
#pragma region TikTacToe

#define EMPTY 0
#define CIRCLE 1
#define CROSS 2

//-------------------------------
// Structures
//-------------------------------

// Position struct, storing the col and row position for the game board.
typedef struct s_position
{
    int row, col;
} Position;

// Constructor of Position
Position new_Position(int row, int col)
{
    Position v = {row, col};
    return v;
}

void printPosition(Position p)
{
    printf("row: %d, col: %d\n", p.row, p.col);
}

// Game board, storing the information of a game board.
// Functions other then the
typedef struct s_tttgameboard
{
    int board[3][3]; // The game board
    int marked;      // how many squares are marked.
} GameBoard_TTT;

//-------------------------------
// Function prototypes
//-------------------------------
void initGameBoard_TTT(GameBoard_TTT *);

//-------------------------------
// Game Board
//-------------------------------
// Create and return a new Game Board
GameBoard_TTT new_GameBoard_TTT()
{
    GameBoard_TTT gb = {{EMPTY}, 0};

    initGameBoard_TTT(&gb);

    return gb;
}

/* Initialize the game board by setting all nine squares to EMPTY */
void initGameBoard_TTT(GameBoard_TTT *gameBoard)
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
int isFull_TTT(GameBoard_TTT *gameBoard)
{
    return gameBoard->marked == 9;
}

// Get the mark from the board
int getMark_TTT(GameBoard_TTT *gameBoard, Position pos)
{
    return gameBoard->board[pos.row][pos.col];
}

// Return true if the specific square is empty
int isMarked_TTT(GameBoard_TTT *gameBoard, Position pos)
{
    return getMark_TTT(gameBoard, pos) != EMPTY;
}

// Get the number of the squre by the array index.
int getNumberByPosition_TTT(Position pos)
{
    return 3 * pos.row + pos.col + 1;
}

// Get the position on board by the squre number.
Position getPositionByNumber_TTT(int num)
{
    // Verify the input
    if (num < 1 || num > 9)
    {
        printf("Invalid square number!");
        return new_Position(-1, -1);
    }

    return new_Position((num - 1) / 3, (num - 1) % 3);
}

int hasWinner_TTT(GameBoard_TTT *gameBoard)
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
void printGameBoard_TTT(GameBoard_TTT *gameBoard)
{
    printf("============\n");
    // Start from the last row
    for (int row = 2; row >= 0; row--)
    {
        // Start from the frist col
        for (int col = 0; col < 3; col++)
        {
            if (gameBoard->board[row][col] == EMPTY) // Empty. Print out the number
            {
                printf("|%d| ", getNumberByPosition_TTT(new_Position(row, col)));
            }
            else if (gameBoard->board[row][col] == CIRCLE) // Circle. Print 'O'
            {
                printf("|O| ");
            }
            else if (gameBoard->board[row][col] == CROSS) // Cross. Print 'X'
            {
                printf("|X| ");
            }
        }
        // Next line
        printf("\n");
    }
    printf("============\n");
}

void debug_PrintGameBoard_TTT(GameBoard_TTT *gb)
{
    printf("====================================\n");
    // Start from the last row
    for (int row = 2; row >= 0; row--)
    {
        // Start from the frist col
        for (int col = 0; col < 3; col++)
        {
            printf("||%p||", &(gb->board[row][col]));
        }
        // Next line
        printf("\n");
    }
    printf("======================================\n");
    // Start from the last row
    for (int row = 2; row >= 0; row--)
    {
        // Start from the frist col
        for (int col = 0; col < 3; col++)
        {
            printf("||%d||", (gb->board[row][col]));
        }
        // Next line
        printf("\n");
    }
    printf("======================================\n");
}
#pragma endregion

// Base function of placing a mark on a board
void placeMark_TTT(GameBoard_TTT *gameBoard, Position pos, int mark)
{
    // Mark the game board
    gameBoard->board[pos.row][pos.col] = mark;

    // Increase the count
    gameBoard->marked++;
}
#pragma endregion

// Get and verify the input until a valid input is received
// Ignoring the player id
int getInputFromHuman_TTT()
{
    // Print message
    printf("Place your mark on an empty space!\n");

    return getNumberInput();
}

// Return a random empty square
int getInputFromComputer_TTT(GameBoard_TTT *gb)
{
    if (isFull_TTT(gb))
    {
        // The game board is fulled, and this function should not even be called
        printf("!!!!! Fatal ERROR, game board is fulled but still asking for computer input !!!!!\n");
        return -1;
        // The above lines is actually never executed because the loop is perfect.
    }

    int ipt = 0;

    do
    {
        ipt = getRandomInt(9) + 1;
    } while (getMark_TTT(gb, getPositionByNumber_TTT(ipt)) != EMPTY);

    return ipt;
}

//-------------------------------
// Game Logic
//-------------------------------
// Get the input from the player and return it as a position in game board
Position getInputFromPlayer_TTT(GameBoard_TTT *gameBoard, Player *player)
{
    int ipt = 0;
    if (player->type == Human)
    {
        // Human player
        ipt = getInputFromHuman_TTT();
    }
    else
    {
        // Computer player
        ipt = getInputFromComputer_TTT(gameBoard);
    }

    // Validate input
    if (ipt == 0)
    {
        printf("/// Invalid input! The number should not be 0!///\n");
        return getInputFromPlayer_TTT(gameBoard, player);
    }

    // Convert the input to Position
    Position p = getPositionByNumber_TTT(ipt);

    // Verify the Input
    if (isMarked_TTT(gameBoard, p))
    {
        // The square is marked. Ask for another input.
        printf("/// The square [%d] has been marked! Choose another square! ///\n", ipt);
        // DEBUG
        // printf("|||||||||||||||||||||||||||||||||||||\n");
        // printGameBoard_TTT(gameBoard);
        // printPosition(p);
        // printf("Mark on p: %d\n", getMark_TTT(gameBoard, p));
        // debug_PrintGameBoard_TTT(gameBoard);
        // printf("|||||||||||||||||||||||||||||||||||||\n");
        return getInputFromPlayer_TTT(gameBoard, player);
    }

    return p;
}

// Invoke to start the Tik Tac Toe game loop.
// p2: the player type of player 2. Human => 0; Computer => 1
void startTikTacToe(PlayerType p2Type)
{
    cls();
    // Initialize game data
    GameBoard_TTT _gb = new_GameBoard_TTT();
    GameBoard_TTT *gameBoard = &_gb;

    // Intialize players
    Player _p[2] = {new_Player(0, Human),
                    new_Player(1, p2Type)}; // Array to store the players

    Player *player[2] = {&_p[0], &_p[1]}; // Pointer array of the players

    int currentTurn = 1; // current turn. 0 => player 1, 1 => player 2

    while (!hasWinner_TTT(gameBoard) && !isFull_TTT(gameBoard))
    {
        printGameBoard_TTT(gameBoard);
        // Switch turn
        currentTurn = (currentTurn == 1) ? 0 : 1;

        // Start turn
        onStartTurn(player[currentTurn]);

        // Ask for Input
        Position p = getInputFromPlayer_TTT(gameBoard, player[currentTurn]);

        // Place mark
        placeMark_TTT(gameBoard, p, player[currentTurn]->mark);

        printf("\n\n");
    }

    // Show end game report. Pass in NULL if no winner
    displayEndGameReport(hasWinner_TTT(gameBoard) ? player[currentTurn] : NULL);

    printGameBoard_TTT(gameBoard);

    // Pause the program until the player pressed Enter key
    waitForEnterKey();

    // Game Loop ended. Return back to where the function is called
}
#pragma endregion
#endif