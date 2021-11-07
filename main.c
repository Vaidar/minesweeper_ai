#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "game.h"

int main(void) {
    srand(time(NULL));
    game *g = game_new(50, 25, 200);
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
    }
    game_free(g);
    exit(0);
}