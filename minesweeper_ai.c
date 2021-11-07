#include <stdio.h>
#include <stdlib.h>
#include "minesweeper_ai.h"
#include "game.h"

int guess_reveal(game *g) {
    int x, y;
    do {
        x = rand() % g->width;
        y = rand() % g->height;
    } while (g->board[y][x].state != CELL_STATE_HIDDEN);
    return reveal_cell(g, x, y);
}

int try_reveal_cell(minesweeper_ai *ai, int x, int y, game *g) {
    if (g->board[y][x].state == CELL_STATE_HIDDEN) {
        return 0;
    }

    int neighbours[8][2];
    int hidden_neighbours = 0;
    int flagged_neighours = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            if (x + dx < 0 || x + dx >= g->width) continue;
            if (y + dy < 0 || y + dy >= g->height) continue;

            switch (g->board[y + dy][x + dx].state) {
            case CELL_STATE_FLAGGED:
                flagged_neighours++;
                break;
            case CELL_STATE_HIDDEN:
                neighbours[hidden_neighbours][0] = y + dy;
                neighbours[hidden_neighbours++][1] = x + dx;
                break;
            default:
                break;
            }
        }
    }

    if (flagged_neighours == g->board[y][x].nearby_mines && hidden_neighbours > 0) {
        for (int i = 0; i < hidden_neighbours; i++) {
            if (reveal_cell(g, neighbours[i][1], neighbours[i][0]) != 0) {
                return 1;
            }
        }
        ai->has_to_guess = 1;
    }
    return 0;
}

void check_if_flag(int x, int y, cell **board, int width, int height) {
    cell *neighbours[8];
    int hidden_neighbours = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            if (x + dx < 0 || x + dx >= width) continue;
            if (y + dy < 0 || y + dy >= height) continue;
            if (board[y + dy][x + dx].state == CELL_STATE_HIDDEN || board[y + dy][x + dx].state == CELL_STATE_FLAGGED) {
                neighbours[hidden_neighbours++] = &board[y + dy][x + dx];
                // More hidden neighbours than bombs so we cannot be sure to flag.
                if (hidden_neighbours > board[y][x].nearby_mines) {
                    return;
                }
            }
        }
    }

    if (hidden_neighbours == board[y][x].nearby_mines && hidden_neighbours > 0) {
        for (int i = 0; i < hidden_neighbours; i++) {
            neighbours[i]->state = CELL_STATE_FLAGGED;
        }
    }
}