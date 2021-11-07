#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define EMPTY 0
#define MINE 1

#define CELL_STATE_HIDDEN 0
#define CELL_STATE_SHOWN 1
#define CELL_STATE_FLAGGED 2

#define CELL_STATE_HIDDEN_CHAR "██"
#define CELL_STATE_MINE_CHAR "* "
#define CELL_STATE_FLAGGED_CHAR "F "

#define BORDER_TOP "═"
#define BORDER_BOTTOM "═"
#define BORDER_SIDE "║"
#define BORDER_CORNER_TOP_LEFT "╔"
#define BORDER_CORNER_TOP_RIGHT "╗"
#define BORDER_CORNER_BOTTOM_LEFT "╚"
#define BORDER_CORNER_BOTTOM_RIGHT "╝"

typedef struct {
    int type;
    int state;
    int nearby_mines;
} cell;

typedef struct {
    int width, height;
    int mines;
    cell **board;
} game;

game *game_new(int width, int height, int mines);
void reveal_cell(game *g, int x, int y);
void draw_board(game *g);
void game_free(game *g);

#endif