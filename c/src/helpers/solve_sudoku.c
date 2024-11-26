#include "print_sudoku.h"
#include "walk.h"
#include <stdio.h>
#include <stdlib.h>

void solve_sudoku(struct Sudoku *sdk) {
    print_sudoku(sdk);
    sdk->initialized = true;
    if (!walk(sdk->board[0][0][0])) {
        perror("Could not solve your Sudoku");
        exit(EXIT_FAILURE);
    }

    if (!ticker) print_sudoku(sdk);
}
