#include <stdio.h>
#include <stdlib.h>

#ifndef Genetic
#define Genetic
#pragma region Genetic
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
#endif // !Genetic