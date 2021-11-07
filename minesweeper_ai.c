/*
    Gå igenom hela fältet och lägg ut flaggor eller öppna celler.

    Att lägga ut flagga:
        Om en cell har lika många gömda grannar som grannbomber,
        flagga alla grannar, annars låt vara.
    
    Att öppna celler:
        Om en cell har lika många flaggade grannar som grannbomber,
        öppna alla oflaggade, annars låt vara.
*/

#include "minesweeper_ai.h"

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