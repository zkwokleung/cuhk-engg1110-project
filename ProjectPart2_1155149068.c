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
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma region Genetic

#define EMPTY 0
#define CIRCLE 1
#define CROSS 2

// Clear the console
void cls()
{
    // Some what clear the console
    // Since system("cls") and system("clear") depends on the platform, it is unsafe to use.
    for (int i = 0; i < 50; i++)
    {
        printf("\n");
    }
}

// Return a random number between 0 and maxValue
int getRandomInt(int maxValue)
{
    return rand() % maxValue;
}

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

Player new_Player(int id, PlayerType type)
{
    Player p = {id, type, 0};
    p.mark = id + 1; // id = 0: CIRCLE, id = 1: CROSS
    return p;
}

// Genetic Event
// Call when before the player start its turn
void onStartTurn(Player *player)
{
    // Promp start turn message
    if (player->type == Human)
    {
        // Human
        printf("Player %d's turn . . .\n", player->id + 1);
    }
    else
    {
        // Computer
        printf("Computer's turn . . .\n");
    }
}

// Display the end game report
void displayEndGameReport(Player *winner)
{
    printf("||||||||||||||||||||||||||||||\n");
    printf("||         Game Over        ||\n");
    printf("||||||||||||||||||||||||||||||\n");
    if (winner != NULL)
    {
        // Display winner's info
        printf("||                          ||\n");
        printf("||   Winner: Player %d       ||\n", winner->id + 1);
        printf("||                          ||\n");
    }
    else
    {
        // Draw game
        printf("||                          ||\n");
        printf("||           Draw           ||\n");
        printf("||                          ||\n");
    }
    printf("||||||||||||||||||||||||||||||\n");
}

#pragma endregion

#pragma region Input
// Standard get input function for this project.
// Read only 1 character each time.
char getChar()
{
    char next;     // temporary storage for the new input
    char ipt;      // Storage for the last entered
    int count = 0; // Counting how many character has been typed.

    printf("> ");

    // Keep reading the input until there is a enter key
    while (1)
    {
        next = fgetc(stdin);

        // Break there loop since the enter key is pressed.
        if (next == '\n')
            break;

        // Otherwise, store the last input character input
        ipt = next;

        // Increase the count
        count++;
    }

    // Invalid Input checking
    // Recursively ask the player until there is a valid input
    if (count > 1) // CONDITION: more than one character input
    {
        printf("/// Invalid Input! Please enter 1 character each time! ///\n");
        return getChar();
    }
    else if (count < 1) // CONDITION: No character Input
    {
        printf("/// You must enter 1 character! ///\n");
        return getChar();
    }

    return ipt;
}

// Get the character input from the player and process it to int between 0 ~ 9
int getNumberInput()
{
    // Get input
    int res = getChar() - '0';

    // Input validation
    if (res >= 0 && res <= 9) // CONDITION: input is a number
        return res;

    // Invalid Input.
    // Recursively ask the player until there is a valid input
    printf("/// Invalid input! Only numeric characters allowed! /// \n");
    return getNumberInput();
}

// Get confirmation from the user
// Y: invoke the callback and return 1; N: return 0; otherwise: Ask again
int getUserConfirm()
{
    printf("Are you sure? (Y/N) ");
    char ipt = getChar();

    switch (ipt)
    {
    case 'Y':
    case 'y':
        return 1;

    case 'N':
    case 'n':
        return 0;

    default:
        printf("/// Invalid input! Please enter 'Y' for Yes and 'N' for No///\n");
        return getUserConfirm();
    }
}

// Call this function to pause the console until the player press ENTER
void waitForEnterKey()
{
    printf("Press Enter to continue . . . \n");

    char tmp;

    // Keep looping until the enter key is pressed
    while (1)
    {
        tmp = fgetc(stdin);

        if (tmp == '\n')
            break;
    }
    // Use looping to discard all the character input
}
#pragma endregion

#pragma region TikTacToe

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
    Player _p[2] = {new_Player(0, Human),
                    new_Player(1, p2Type)};
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

#pragma region Menu
void startMainMenu();
void startTTTMenu();
void startC4Menu();

// Main Menu
void printMainMenu()
{
    printf("==============================\n");
    printf("||  Welcome to my project!  ||\n");
    printf("==============================\n");
    printf("|| Choose a game mode:      ||\n");
    printf("||  [1] Tik-Tac-Toe         ||\n");
    printf("||  [2] Connect 4           ||\n");
    printf("||  [0] Exit                ||\n");
    printf("------------------------------\n");
}

// Evaluate the user input for the main menu
void evaluateMainMenuInput(int input)
{
    switch (input)
    {
    case 1:
        startTTTMenu();
        break;

    case 2:
        startC4Menu();
        break;

    case 0:
        // Ask before exiting
        if (getUserConfirm())
        {
            exit(0);
        }
        break;

    default:
        // Invalid input. Recursively call until a valid input is detected
        printf("/// Option Unavailable! ///\n");
        evaluateMainMenuInput(getNumberInput());
    }
}

// Initialize and display the main menu
void startMainMenu()
{
    cls();
    // Display Main menu
    printMainMenu();

    // Get user input
    evaluateMainMenuInput(getNumberInput());
}

void printGenericGameOptions()
{
    printf("|| Choose an option:        ||\n");
    printf("||  [1] Single Player       ||\n");
    printf("||  [2] Multiplayer         ||\n");
    printf("||  [0] Back                ||\n");
    printf("------------------------------\n");
}

// New Game MENU
void printTTTMenu()
{
    printf("==============================\n");
    printf("||       Tik-Tac-Toe        ||\n");
    printf("==============================\n");
    printGenericGameOptions();
}

void printC4Menu()
{
    printf("==============================\n");
    printf("||        Connect 4         ||\n");
    printf("==============================\n");
    printGenericGameOptions();
}

void evaluateTTTMenuInput(int input)
{
    switch (input)
    {
    case 1:
        startTikTacToe(Computer);
        break;

    case 2:
        startTikTacToe(Human);
        break;

    case 0:
        // Return to the main menu
        return;

    default:
        // Invalid input. Recursively call until received valid input
        printf("/// Option Unavailable! ///\n");
        evaluateTTTMenuInput(getNumberInput());
    }
}

void evaluateC4MenuInput(int input)
{
    switch (input)
    {
    case 1:
        startConnect4(Computer);
        break;

    case 2:
        startConnect4(Human);
        break;

    case 0:
        // Return to the main menu
        return;

    default:
        // Invalid input. Recursively call until received valid input
        printf("/// Option Unavailable! ///\n");
        evaluateTTTMenuInput(getNumberInput());
    }
}

// Initialize the game menu
void startTTTMenu()
{
    cls();
    // Display options
    printTTTMenu();

    // Get user Input
    evaluateTTTMenuInput(getNumberInput());

    // Always return to the main menu after the inner loop completed
    startMainMenu();
}

void startC4Menu()
{
    cls();

    // Display options
    printC4Menu();

    //Get user Input
    evaluateC4MenuInput(getNumberInput());

    // Always return to the main menu after the inner loop completed
    startMainMenu();
}
#pragma endregion

/* The main function */
int main()
{
    // Initialize random number generator
    srand(time(NULL));

    // Let the internal logic to terminate the program
    while (1)
    {
        startMainMenu();
    }

    return 0;
}