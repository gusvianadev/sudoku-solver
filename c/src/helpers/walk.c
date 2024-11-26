#include "cell.h"
#include "solve_cell.h"

bool walk(struct Cell *cell) {
    struct Cell *tmp_cell = cell;

    while (tmp_cell && tmp_cell->value) tmp_cell = tmp_cell->next;
    return !tmp_cell || solve_cell(tmp_cell);
}
