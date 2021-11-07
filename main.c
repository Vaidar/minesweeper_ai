#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "game.h"
#include "minesweeper_ai.h"

#define SLEEP_TIME 100000

void exit_game(game *g, int status);

// Otroligt optimiserad. Kollar alla rutor hela tiden flera gånger i onödan.
int main(void) {
    srand(time(NULL));
    game *g = game_new(25, 25, 100);
    minesweeper_ai *ai = calloc(1, sizeof(minesweeper_ai));
    
    if (guess_reveal(g) != 0) {
        exit_game(g, 1);
    }
    while (1) {
        for (int y = 0; y < g->height; y++) {
            for (int x = 0; x < g->width; x++) {
                check_if_flag(x, y, g->board, g->width, g->height);
                if (try_reveal_cell(ai, x, y, g) != 0) {
                    exit_game(g, 1);
                }
            }
            system("clear");
            draw_board(g);
            usleep(SLEEP_TIME);
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
    if (status != 0) fprintf(stderr, "You lost!\n");

    game_free(g);
    printf("\n");
    exit(status);
}