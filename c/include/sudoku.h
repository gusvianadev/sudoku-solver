#ifndef SUDOKU
#define SUDOKU

#include "u_t.h"

typedef struct Cell *quadrant[3][3];
typedef quadrant board_t[9];

struct SdkPosition {
    u16 y;
    u16 x;
};

struct Sudoku {
    board_t board;
    struct SdkPosition pos;
    bool initialized;
};

extern u64 ticker;
extern struct SdkPosition final_position;
#endif
