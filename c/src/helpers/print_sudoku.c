#include "cell.h"
#include "print_cell.h"
#include "sudoku.h"
#include "term/actions.h"
#include <stdio.h>

#define AUDIO_COMMAND \
    (system("command -v paplay > /dev/null 2>&1") == 0 ? "paplay" : "aplay")
#define MIN_TICKER_SOUND 100000

void print_sudoku(struct Sudoku *sdk) {
    printf(MOVE_CURSOR_TO, sdk->pos.y, sdk->pos.x);
    struct Cell *cell = sdk->board[0][0][0];

    do print_cell(&sdk->pos, cell);
    while ((cell = cell->next));
}
