#include <stdio.h>
#include <stdlib.h>
#include "Input.h"
#include "TikTacToe.h"
#include "Connect4.h"

#ifndef MENU
#define MENU
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
    int ended = 0;
    while (!ended)
    {
        cls();
        // Display Main menu
        printMainMenu();

        // Get user input
        evaluateMainMenuInput(getNumberInput());
    }
}

void printGeneticGameOptions()
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
    printGeneticGameOptions();
}

void printC4Menu()
{
    printf("==============================\n");
    printf("||        Connect 4         ||\n");
    printf("==============================\n");
    printGeneticGameOptions();
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
#endif // !MENU