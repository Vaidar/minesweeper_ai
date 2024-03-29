#ifndef MINESWEEPER_AI_H
#define MINESWEEPER_AI_H

#include "game.h"

// Borde ha en lista över gömda rutor så att den slipper loopa genom allt hela tiden.
typedef struct {
    int has_to_guess;
} minesweeper_ai;

int guess_reveal(game *g);
int try_reveal_cell(minesweeper_ai *ai, int x, int y, game *g);
void check_if_flag(int x, int y, cell **board, int width, int height);

#endif