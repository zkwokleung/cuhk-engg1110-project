#include <stdio.h>

#ifndef Genetic
#define Genetic
#pragma region Genetic
// Clear the console
void cls()
{
    // Some what clear the console
    // Since system("cls") depends on the platform, it is unsave to use.
    for (int i = 0; i < 50; i++)
    {
        printf("\n");
    }
}
#pragma endregion
#endif // !Genetic