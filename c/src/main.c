#include "prepare_sudokus.h"
#include "solve_sudoku.h"
#include "u_t.h"
#include "term/actions.h"
#include <getopt.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define HELP \
    "[--t | --ticker] ticker: The waiting seconds between each cell iteration. " \
    "It can be anywhere from 0.0 to 60.0. " \
    "Floating point numbers are allowed.\n" \
    "[-h | --help] | print this help\n" \
    "Examples:\n" \
    "sudoku-solver ./sudoku_file\n" \
    "sudoku-solver ./sudoku_file -t 0.2\n"
#define NUM_THREADS 9

u64 ticker = 0;
struct SdkPosition final_position = {.y = 1, .x = 1};

struct ThreadData {
    struct Sudoku *sudoku;
};

void *solve_sudoku_thread(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    solve_sudoku(data->sudoku);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror(
            "You must provide file containing your Sudokus as a first argument\n"
        );
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r+");

    if (!file) {
        perror("Error opening your file");
        exit(EXIT_FAILURE);
    }

    int opt;
    const struct option options[] = {
        {"ticker", required_argument, NULL, 't'},
        {"sudoku", required_argument, NULL, 's'},
        {"h", no_argument, NULL, 'h'}
    };

    while ((opt = getopt_long(argc, argv, "t:s:h", options, NULL)) != -1) {
        switch (opt) {
            case 't':
                char *endptr;
                float value;
                float tmp = strtof(optarg, &endptr);

                if (*endptr != '\0' || optarg == endptr || value < 0 ||
                    value > 60) {
                    perror("Ticker must be a number between 0 and 60");
                    exit(EXIT_FAILURE);
                }
                ticker = floorf(tmp * 1000000);
                break;
            case 'h':
                printf(HELP);
                exit(0);
            default:
                fprintf(stderr, HELP);
                exit(EXIT_FAILURE);
        }
    }

    u64 size_counter = 0;
    struct Sudoku **sudokus = prepare_sudokus(file, &size_counter);

    printf(CLEAR);
    printf(CURSOR_INVISIBLE);

    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < size_counter; i++) {
        struct ThreadData *data = malloc(sizeof(struct ThreadData));
        if (!data) {
            perror("Not enough memory");
            exit(EXIT_FAILURE);
        }
        data->sudoku = sudokus[i];
        pthread_create(&threads[i], NULL, solve_sudoku_thread, (void *)data);
    }

    for (int i = 0; i < size_counter; i++) pthread_join(threads[i], NULL);

    printf(RESET_ALL);
    printf(MOVE_CURSOR_TO, final_position.y, final_position.x);
    printf("\n");
    return 0;
}
