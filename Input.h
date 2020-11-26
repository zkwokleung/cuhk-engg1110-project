#include <stdio.h>

#ifndef Input
#define Input
// standard get input function for this project.
// Get the character input from the player and process it to int between 0 ~ 9
int getUserInput()
{
    char *ipt;
    printf("> ");
    fgets(ipt, 2, stdin);

    // Verify the Input
    if (*ipt >= 1 && *ipt <= 9)
    {
        return *ipt - '0';
    }

    // Invalid Input.
    // Recursively ask the player until there is a valid input
    printf("/// Invalid input! Input must between 0 and 9! /// \n");
    return getUserInput();
}

#endif // !Input