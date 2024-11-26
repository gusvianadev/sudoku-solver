#ifndef CELL
#define CELL
#include "sudoku.h"
#include "u_t.h"

struct Position {
    u8 quad;
    u8 row;
    u8 col;
};

struct Quadrant {
    quadrant *self;
    quadrant *top;
    quadrant *right;
    quadrant *bottom;
    quadrant *left;
    board_t *board;
};

struct Cell {
    u8 value;
    struct Position pos;
    struct SdkPosition pos_in_board;
    struct Cell *top;
    struct Cell *right;
    struct Cell *bottom;
    struct Cell *left;
    struct Cell *next;
    struct Cell *prev;
    struct Cell *prev_in_quad;
    struct Cell *next_in_quad;
    struct Quadrant quadrants;
    char *style;
    board_t *board;
    struct Sudoku *sdk;
};

#endif
