#include "cell.h"
#include "quad_position.h"
#include "sudoku.h"
#include "term/colors.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MEMORY_ERROR "Not enough memory"

struct Sudoku *create_sudoku(FILE *file, int *c, u16 pos_y, u16 pos_x);

struct Sudoku **prepare_sudokus(FILE *file, u64 *size_counter) {
    struct Sudoku **sudokus = malloc(sizeof(struct Sudoku *));

    if (!sudokus) {
        perror(MEMORY_ERROR);
        exit(EXIT_FAILURE);
    }

    int c;
    int i = 0;
    while (c != EOF) {
        u16 pos_y = quad_row(i) * 12 + 1;
        u16 pos_x = quad_col(i) * 24 + 1;
        struct Sudoku *sudoku = create_sudoku(file, &c, pos_y, pos_x);

        if (!sudoku) {
            if (i == 0) {
                perror("There are no Sudokus in your file");
                exit(EXIT_FAILURE);
            }
            free(sudoku);
            break;
        }

        struct Sudoku **tmp =
            realloc(sudokus, (i + 1) * sizeof(struct Sudoku *));

        if (!tmp) {
            perror(MEMORY_ERROR);
            exit(EXIT_FAILURE);
        }

        sudokus = tmp;
        sudokus[i++] = sudoku;
    }

    *size_counter = i;
    final_position = sudokus[i - 1]->pos;
    final_position.y = final_position.y + 11;
    return sudokus;
}

struct Cell *create_cell(
    struct Cell *prev_cell,
    struct Cell *top_row[],
    u8 quad,
    u8 row,
    u8 col,
    u8 value,
    struct Sudoku *sudoku
) {
    struct Cell *cell = malloc(sizeof(struct Cell));
    if (!cell) {
        perror(MEMORY_ERROR);
        exit(EXIT_FAILURE);
    }

    struct Cell *top_cell = top_row[col + quad_col(quad) * 3],
                *left_cell =
                    prev_cell && prev_cell->pos.row == row ? prev_cell : NULL,
                *prev_in_quad = NULL;
    if (col > 0) prev_in_quad = prev_cell;
    else if (row > 0) prev_in_quad = sudoku->board[quad][row - 1][2];

    struct SdkPosition sdk_pos = sudoku->pos;
    const u8 left_padding = 1;
    const u8 chars_per_col = 4; // 3 cells + separator
    const u8 chars_per_cell = 2; // cell + left padding
    const u8 chars_per_row =
        8; // 3 cells + 3 cell left padding + 1 separator + 1 separator padding

    *cell = (struct Cell){
        .board = &sudoku->board,
        .sdk = sudoku,
        .value = value,
        .pos = {.quad = quad, .row = row, .col = col},
        .pos_in_board =
            {.y = sdk_pos.y + row + quad_row(quad) * chars_per_col,
             .x = sdk_pos.x + left_padding + col * chars_per_cell +
                 quad_col(quad) * chars_per_row},
        .style = !value ? RED : "",
        .prev = prev_cell,
        .next = NULL,
        .top = top_cell,
        .right = NULL,
        .bottom = NULL,
        .left = left_cell,
        .prev_in_quad = prev_in_quad,
        .next_in_quad = NULL,
        .quadrants =
            {
                .self = &sudoku->board[quad],
                .top = quad > 2 ? &sudoku->board[quad - 3] : NULL,
                .right = quad_col(quad) < 2 ? &sudoku->board[quad + 1] : NULL,
                .bottom = quad < 6 ? &sudoku->board[quad + 3] : NULL,
                .left = quad_col(quad) > 0 ? &sudoku->board[quad - 1] : NULL,
            },
    };

    if (left_cell) left_cell->right = cell;
    if (prev_cell) prev_cell->next = cell;
    if (top_cell) top_cell->bottom = cell;
    if (prev_in_quad) prev_in_quad->next_in_quad = cell;

    return cell;
}

struct Sudoku *create_sudoku(FILE *file, int *c, u16 pos_y, u16 pos_x) {
    struct Sudoku *sudoku = malloc(sizeof(struct Sudoku));
    if (!sudoku) {
        perror(MEMORY_ERROR);
        exit(EXIT_FAILURE);
    }

    *sudoku = (struct Sudoku
    ){.board = {}, .initialized = false, .pos = {.y = pos_y, .x = pos_x}};

    struct Cell *prev_cell = NULL, *top_row[9] = {NULL};

    u8 quad = 0, row = 0, col = 0;
    while ((*c = fgetc(file)) != EOF && quad < 9) {
        u8 value = *c == '.' ? 0 : isdigit(*c) ? *c - '0' : 10;
        if (value < 0 || value > 9) continue;
        struct Cell *cell =
            create_cell(prev_cell, top_row, quad, row, col, value, sudoku);

        prev_cell = cell;
        top_row[col + quad_col(quad) * 3] = cell;
        sudoku->board[quad][row][col++] = cell;

        if (col == 3) {
            col = 0;

            if (quad_col(quad) == 2) {
                if (row < 2) {
                    quad -= 2;
                    row++;
                    continue;
                }
                row = 0;
            }

            quad++;
        }
    }

    if (quad < 9) return NULL;
    return sudoku;
}
