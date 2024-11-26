#include "print_cell.h"
#include "walk.h"
#include "term/colors.h"
#include <stdio.h>

#define CHECKING_SOUND_PATH "assets/checking.wav"
#define VALID_SOUND_PATH "assets/valid.wav"
#define INVALID_SOUND_PATH "assets/invalid.wav"

bool solve_cell(struct Cell *cell) {
    bool is_valid = false;
    struct Position pos = cell->pos;
    struct Cell *tmp, *neighbor_quad_cell_start[4] = {NULL};
    struct Sudoku *sdk = cell->sdk;

    if (*cell->quadrants.top)
        neighbor_quad_cell_start[0] = (*cell->quadrants.top)[2][pos.col];
    if (*cell->quadrants.right)
        neighbor_quad_cell_start[1] = (*cell->quadrants.right)[pos.row][0];
    if (*cell->quadrants.bottom)
        neighbor_quad_cell_start[2] = (*cell->quadrants.bottom)[0][pos.col];
    if (*cell->quadrants.left)
        neighbor_quad_cell_start[3] = (*cell->quadrants.left)[pos.row][2];

    while (!is_valid && (cell->value += 1) <= 9) {
        is_valid = true;
        if (ticker) {
            cell->style = YELLOW;
            print_cell(&sdk->pos, cell);
        }

        for (int i = 0; i < 4; i++) {
            tmp = neighbor_quad_cell_start[i];

            while (tmp) {
                if (tmp->value == cell->value) {
                    is_valid = false;
                    break;
                }
                tmp = i == 0 ? tmp->top
                    : i == 1 ? tmp->right
                    : i == 2 ? tmp->bottom
                             : tmp->left;
            }
            if (!is_valid) break;
        }

        if (!is_valid) continue;

        struct Cell *prev_in_quad = cell->prev_in_quad;
        while (prev_in_quad) {
            if (prev_in_quad->value == cell->value) {
                is_valid = false;
                break;
            }
            prev_in_quad = prev_in_quad->prev_in_quad;
        }

        if (!is_valid) continue;

        struct Cell *next_in_quad = cell->next_in_quad;
        while (next_in_quad) {
            if (next_in_quad->value == cell->value) {
                is_valid = false;
                break;
            }
            next_in_quad = next_in_quad->next_in_quad;
        }

        if (is_valid) {
            cell->style = GREEN;
            if (ticker) print_cell(&sdk->pos, cell);

            is_valid = walk(cell->next);
        }
    }

    if (!is_valid) {
        if (ticker) {
            cell->value = 9;
            cell->style = RED;
            print_cell(&sdk->pos, cell);
            cell->value = 0;
            print_cell(&sdk->pos, cell);
        }
        cell->value = 0;
    }

    return is_valid;
}
