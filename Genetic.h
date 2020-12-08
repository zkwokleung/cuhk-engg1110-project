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
#pragma endregion
#endif // !Genetic