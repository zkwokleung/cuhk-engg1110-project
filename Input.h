#include <stdio.h>

#ifndef Input
#define Input
// standard get input function for this project.
// Get the character input from the player and process it to int between 0 ~ 9
int getUserInput()
{
    char ipt;
    printf("> ");
    fgets(&ipt, 1000, stdin);

    int result = ipt - '0';
    // printf("Debug: you entered %d", result);

    // Verify the Input
    if (result >= 0 && result <= 9)
    {
        return result;
    }

    // Invalid Input.
    // Recursively ask the player until there is a valid input
    printf("/// Invalid input! Input must between 0 and 9! /// \n");
    return getUserInput();
}

// Get confirmation from the user
// Y: invoke the callback and return 1; N: return 0; other: Ask again
int getUserConfirm(void (*callback)())
{
    char ipt;

    printf("Are you sure? (Y/N) > ");
    fgets(&ipt, 20, stdin);

    switch (ipt)
    {
    case 'Y':
    case 'y':
        return 1;

    case 'N':
    case 'n':
        return 0;

    default:
        printf("/// Invalid input! ///\n");
        return getUserConfirm(callback);
    }
}

// Call this function to pause the console until the player press ENTER
void waitForEnterKey()
{
    printf("Press Enter to continue . . . \n");
    char tmp = 0;
    while (tmp != '\r' && tmp != '\n')
    {
        // Throw away all the character except the enter key
        tmp = getchar();
    }
}
#endif // !Input
