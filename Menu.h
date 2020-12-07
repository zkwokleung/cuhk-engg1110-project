#include <stdio.h>
#include <stdlib.h>
#include "Input.h"
#include "TikTacToe.h"

#ifndef MENU
#define MENU
#pragma region Menu
void startMainMenu();
void startNewGameMenu();

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
        startNewGameMenu();
        break;

    case 2:

        break;

    case 0:
        exit(0);
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
    int ended = 0;
    while (!ended)
    {
        // Display Main menu
        printMainMenu();

        // Get user input
        evaluateMainMenuInput(getNumberInput());
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
        evaluateNewGameMenuInput(getNumberInput());
    }
}

// Initialize the new game menu
void startNewGameMenu()
{
    cls();
    // Display options
    printNewGameMenu();

    // Get user Input
    evaluateNewGameMenuInput(getNumberInput());

    // Always return to the main menu after the inner loop completed
    startMainMenu();
}
#pragma endregion
#endif // !MENU