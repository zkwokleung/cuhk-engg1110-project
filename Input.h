#include <stdio.h>

#ifndef Input
#define Input
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
#endif // !Input
