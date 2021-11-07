#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "game.h"
#include "minesweeper_ai.h"

#define SLEEP_TIME 1000000

void exit_game(game *g, int status);

int main(void) {
    srand(time(NULL));
    game *g = game_new(20, 20, 75);
    minesweeper_ai *ai = calloc(1, sizeof(minesweeper_ai));
    if (guess_reveal(g) != 0) {
        exit_game(g, 1);
    }
    while (1) {
        system("clear");
        draw_board(g);
        usleep(SLEEP_TIME);

        // Random reveals for debug purposes
        // int x, y;
        // do {
        //     x = rand() % g->width;
        //     y = rand() % g->height; 
        // } while (g->board[y][x].state != CELL_STATE_HIDDEN);
        // reveal_cell(g, x, y);

        // system("clear");
        // draw_board(g);
        for (int i = 0; i < g->width; i++) {
            for (int j = 0; j < g->height; j++) {
                check_if_flag(j, i, g->board, g->width, g->height);
                if (try_reveal_cell(ai, j, i, g) != 0) {
                    exit_game(g, 1);
                }
            }
            //system("clear");
            //draw_board(g);
            //usleep(1000000);
        }
        if (ai->has_to_guess == 0) {
            if (guess_reveal(g) != 0) {
                exit_game(g, 1);
            }
        } else {
            ai->has_to_guess = 0;
        }
    }
    exit_game(g, 0);
}

void exit_game(game *g, int status) {
    system("clear");
    draw_board(g);
    if (status != 0) {
        fprintf(stderr, "You lost!\n");
    }
    game_free(g);
    printf("\n");
    exit(status);
}