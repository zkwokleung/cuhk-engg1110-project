#include <stdio.h>
#include "Input.h"

#ifndef TikTacToe
#define TikTacToe

/* Macros used to represent the state of each square */
#define EMPTY 0
#define CIRCLE 1
#define CROSS 2

//-------------------------------
// Structures
//-------------------------------
// Position struct, storing the x(col) and y(row) position for the game board.
typedef struct s_position
{
    int row, col;
} Position;

// Constructor of Position
Position newPosition(int row, int col)
{
    Position v = {row, col};
    return v;
}

// Game board, storing the information of a game board.
// Functions other then the
typedef struct GameBoard
{
    int board[3][3]; // The game board
    int marked;      // how many squares are marked.
} GameBoard;

// Enum for indentifing the player's type.
typedef enum
{
    Human = 0,
    Computer = 1
} PlayerType;

// Storing the information of a Player
typedef struct s_player
{
    int id;
    PlayerType type;
    int move;
    int mark;
} Player;

Player newPlayer(int id, PlayerType type)
{
    Player p = {id, type, 0};
    p.mark = id + 1; // id = 0: CIRCLE, id = 1: CROSS
    return p;
}

//-------------------------------
// Function prototypes
//-------------------------------
void startNewSinglePlayerGame();
void startNewMultiPlayerGame();
void initGameBoard(GameBoard *);

//-------------------------------
// Game Board
//-------------------------------
// Create and return a new Game Board
GameBoard newGameBoard()
{
    GameBoard gb = {{EMPTY}, 0};

    initGameBoard(&gb);

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
    return getMark(gameBoard, pos) != EMPTY;
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
// Ignoring the player id
int getInputFromHuman()
{
    int ipt;

    // Print message
    printf("Place your mark on an empty space!\n");
    return getUserInput();
}

int getInputFromComputer(GameBoard *board)
{
    // Loop through the board to find a empty space
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board->board[i][j] == EMPTY)
                return 3 * i + j + 1;
        }
    }
}

//-------------------------------
// Game Logic
//-------------------------------
// Get the input from the player and return it as a position in game board
Position getInputFromPlayer(GameBoard *gameBoard, Player *player)
{
    int ipt = 0;
    if (player->type == Human)
    {
        // Human player
        ipt = getInputFromHuman();
    }
    else
    {
        // Computer player
        ipt = getInputFromComputer(gameBoard);
    }

    // Convert the input to Position
    Position p = getPositionByNumber(ipt);

    // Verify the Input
    if (isMarked(gameBoard, p))
    {
        // The square is marked. Ask for another input.
        printf("/// The square has been marked! Choose another square! ///");
        return getInputFromPlayer(gameBoard, player);
    }

    return p;
}

// Call when before the player start its turn
void onStartTurn(Player *player)
{
    // Promp start turn message
    if (player->type == Human)
    {
        // Human
        printf("Player %d's turn\n", player->id + 1);
    }
    else
    {
        // Computer
        printf("Computer's turn\n");
    }
}

// Display the end game report
void displayEndGameReport(GameBoard *board, Player *winner)
{
    printf("||||||||||||||||||||||||||||||\n");
    printf("||         Game Over        ||\n");
    printf("||||||||||||||||||||||||||||||\n");
    printf("||\n");
    if (winner != NULL)
    {
        // Display winner's info
        printf("|| Winner: Player %d\n", winner->id + 1);
        printf("||\n");
        printf("|| Placed marks: %d\n", winner->move);
    }
    else
    {
        // Draw game
        printf("||            Draw          ||\n");
    }
    printf("||\n");
    printf("||||||||||||||||||||||||||||||\n");
}

// Invoke to start the Tik Tac Toe game loop.
// p2: the player type of player 2. Human => 0; Computer => 1
void startTikTacToe(PlayerType p2Type)
{
    // Initialize game data
    GameBoard _gb = newGameBoard();
    GameBoard *gameBoard = &_gb;

    // Intialize players
    Player _p[2]; // Array to store the players
    _p[0] = newPlayer(0, Human);
    _p[1] = newPlayer(1, p2Type);

    Player *player[2] = {&_p[0], &_p[1]}; // Pointer array of the players

    int currentTurn = 1; // current turn. 0 => player 1, 1 => player 2

    printGameBoard(gameBoard);

    while (!hasWinner(gameBoard) && !isFull(gameBoard))
    {
        // Switch turn
        currentTurn = (currentTurn == 1) ? 0 : 1;

        // Start turn
        onStartTurn(player[currentTurn]);

        // Ask for Input
        Position p = getInputFromPlayer(gameBoard, player[currentTurn]);

        // Place mark
        placeMark(gameBoard, p, player[currentTurn]->mark);

        printGameBoard(gameBoard);
    }

    printGameBoard(gameBoard);

    // Show end game report. Pass in NULL if no winner
    displayEndGameReport(gameBoard, hasWinner(gameBoard) ? player[currentTurn] : NULL);

    // Pause the program until the player pressed Enter key
    waitForEnterKey();

    // Game Loop ended. Return back to where the function is called
}

#endif
