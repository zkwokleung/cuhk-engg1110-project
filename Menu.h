#include <stdio.h>

#ifndef MENU
#define MENU
// Main Menu
void printMainMenu()
{
    printf("==============================\n");
    printf("||  Welcome to my project!  ||\n");
    printf("==============================\n");
    printf("|| Choose and option:       ||\n");
    printf("||  [1] New game            ||\n");
    printf("||  [2] Load game           ||\n");
    printf("||  [0] Exit                ||\n");
    printf("------------------------------\n");
}

// Evaluate the user input for the main menu
void evaluateMainMenuInput(int input)
{
    switch (input)
    {
    case 1:

        break;

    case 2:

        break;

    case 0:

        break;
    }
}

// New Game MENU
void printNewGameMenu()
{
    printf("==============================\n");
    printf("||        Game Mode         ||\n");
    printf("==============================\n");
    printf("|| Choose and option:       ||\n");
    printf("||  [1] Single Player       ||\n");
    printf("||  [2] Multiplayer         ||\n");
    printf("||  [0] Back                ||\n");
    printf("------------------------------\n");
}
#endif // !MENU