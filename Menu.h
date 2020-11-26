#include <stdio.h>
#include <stdlib.h>
#include "Input.h"

#ifndef MENU
#define MENU
#pragma region prototypes
void StartMainMenu();
void StartNewGameMenu();
#pragma endregion

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
        StartNewGameMenu();
        break;

    case 2:

        break;

    case 0:
        exit(0);
        break;

    default:
        // Invalid input. Recursively call until a valid input is detected
        printf("/// Option Unavailable! ///\n");
        evaluateMainMenuInput(getUserInput());
    }
}

// Initialize and display the main menu
void StartMainMenu()
{
    int ended = 0;
    while (!ended)
    {
        // Display Main menu
        printMainMenu();

        // Get user input
        evaluateMainMenuInput(getUserInput());
    }
}

// New Game MENU
void printNewGameMenu()
{
    printf("==============================\n");
    printf("||         New Game         ||\n");
    printf("==============================\n");
    printf("|| Choose and option:       ||\n");
    printf("||  [1] Single Player       ||\n");
    printf("||  [2] Multiplayer         ||\n");
    printf("||  [0] Back                ||\n");
    printf("------------------------------\n");
}

void evaluateNewGameMenuInput(int input)
{
    switch (input)
    {
    case 1:

        break;

    case 2:

        break;

    case 0:
        // Return to the main menu
        return;

    default:
        // Invalid input. Recursively call until received valid input
        printf("/// Option Unavailable! ///\n");
        evaluateNewGameMenuInput(getUserInput());
    }
}

// Initialize the new game menu
void StartNewGameMenu()
{
    // Display options
    printNewGameMenu();

    // Get user Input
    evaluateNewGameMenuInput(getUserInput());
}
#endif // !MENU