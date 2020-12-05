#include <stdio.h>
#include "Input.h"
#include "TikTacToe.h"
#include "Genetic.h"

#ifndef Connect4
#define Connect4
typedef struct s_gameboardc4
{
    int board[6][7];
    int marked;
} GameBaordC4;

GameBaordC4 newGameBaordC4()
{
    GameBaordC4 gb = {{EMPTY}, 0};

    return gb;
}

void initGameBaordC4(GameBaordC4 *gb)
{
    // Init the board
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            gb->board[row][col] = EMPTY;
        }
    }

    // Init the fields
    gb->marked = 0;
}

int isFullC4(GameBoardC4 *gb)
{
    return gb->marked == 6 * 7;
}
#endif // !Connect4