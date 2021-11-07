#include <stdio.h>
#include <stdlib.h>
#include "game.h"

static cell **board_new(int width, int height, int mines) {
    cell **board = calloc(height, sizeof(cell *));
    for (int i = 0; i < width; i++) {
        board[i] = calloc(width, sizeof(cell));
    }

    for (int i = 0; i < mines; i++) {
        int x, y;
        do {
            x = rand() % width;
            y = rand() % height;
        } while (board[y][x].type == MINE);
        board[y][x].type = MINE;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (board[y][x].type != MINE) {
                board[y][x].type = EMPTY;
            }
            board[y][x].state = CELL_STATE_HIDDEN;
        }
    }

    return board;
}

static void calculate_nearby_mines(game *g) {
    for (int y = 0; y < g->height; y++) {
        for (int x = 0; x < g->width; x++) {
            if (g->board[y][x].type == MINE) {
                g->board[y][x].nearby_mines = -1;
                continue;
            }
            int neighbours = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0) continue;
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx < 0 || nx >= g->width || ny < 0 || ny >= g->height) continue;
                    if (g->board[ny][nx].type == MINE) neighbours++;
                }
            }
            g->board[y][x].nearby_mines = neighbours;
        }
    }
}

static void reveal_all_nearby_empty(game *g, int x, int y) {
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= g->width || ny < 0 || ny >= g->height) continue;
            if (g->board[ny][nx].state == CELL_STATE_HIDDEN && g->board[ny][nx].type == EMPTY) {
                g->board[ny][nx].state = CELL_STATE_SHOWN;
                if (g->board[ny][nx].nearby_mines == 0) {
                    reveal_all_nearby_empty(g, nx, ny);
                }
            }
        }
    }
}

static void draw_border(int x, int y, int width, int height) {
    if (y == -1) { // Top
        if (x == -1 || x == width) { // Top corners
            if (x == -1) { // Top left
                printf(BORDER_CORNER_TOP_LEFT);
            } else { // Top right
                printf(BORDER_CORNER_TOP_RIGHT);
            }
        } else {
            printf(BORDER_TOP);
        }
    } else if (y == height) { // Bottom
        if (x == -1 || x == width) { // Bottom corners
            if (x == -1) { // Bottom left
                printf(BORDER_CORNER_BOTTOM_LEFT);
            } else { // Bottom right
                printf(BORDER_CORNER_BOTTOM_RIGHT);
            }
        } else {
            printf(BORDER_BOTTOM);
        }
    } else { // Sides
        printf(BORDER_SIDE);
    }
}

game *game_new(int width, int height, int mines) {
    game *g = calloc(1, sizeof(game));
    g->width = width;
    g->height = height;
    g->mines = mines;
    g->board = board_new(width, height, mines);
    calculate_nearby_mines(g);
    return g;
}

void reveal_cell(game *g, int x, int y) {
    g->board[y][x].state = CELL_STATE_SHOWN;
    if (g->board[y][x].type == EMPTY && g->board[y][x].nearby_mines == 0) {
        reveal_all_nearby_empty(g, x, y);
    } else if (g->board[y][x].type == MINE) {
        // Lost the game.
    }
}

void draw_board(game *g) {
    for (int y = -1; y <= g->height; y++) {
        for (int x = -1; x <= g->width; x++) {
            if (y == -1 || y == g->height || x == -1 || x == g->width) {
                draw_border(x, y, g->width, g->height);
                continue;
            }

            switch (g->board[y][x].state) {
            case CELL_STATE_HIDDEN:
                printf(CELL_STATE_HIDDEN_CHAR);
                break;
            case CELL_STATE_SHOWN:
                switch (g->board[y][x].type) {
                case MINE:
                    printf(CELL_STATE_MINE_CHAR);
                    break;
                case EMPTY:
                    printf("%d", g->board[y][x].nearby_mines);
                    break;
                }
                break;
            case CELL_STATE_FLAGGED:
                printf(CELL_STATE_FLAGGED_CHAR);
                break;
            default:
                printf("?");
                break;
            }
        }
        printf("\n");
    }
}

void game_free(game *g) {
    for (int i = 0; i < g->height; i++) {
        free(g->board[i]);
    }
    free(g->board);
    free(g);
}