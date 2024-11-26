#ifndef PREPARE_SUDOKUS
#define PREPARE_SUDOKUS

#include <stdio.h>
#include "sudoku.h"
#include "u_t.h"

struct Sudoku **prepare_sudokus(FILE *file, u64 *size_counter);

#endif
