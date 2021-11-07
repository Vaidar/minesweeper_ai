#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "game.h"
#include "minesweeper_ai.h"

int main(void) {
    srand(time(NULL));
    game *g = game_new(20, 20, 75);
    while (1) {
        system("clear");
        draw_board(g);
        usleep(1000000);

        // Random reveals for debug purposes
        int x, y;
        do {
            x = rand() % g->width;
            y = rand() % g->height; 
        } while (g->board[y][x].state != CELL_STATE_HIDDEN);
        reveal_cell(g, x, y);

        system("clear");
        draw_board(g);
        for (int i = 0; i < g->width; i++) {
            for (int j = 0; j < g->height; j++) {
                check_if_flag(j, i, g->board, g->width, g->height);
            }
        }
    }
    game_free(g);
    exit(0);
}