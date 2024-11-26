#include "cell.h"
#include "quad_position.h"
#include "sudoku.h"
#include "unistd.h"
#include "term/actions.h"
#include "term/colors.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_TICKER_SOUND 100000
#define AUDIO_COMMAND \
    (system("command -v paplay > /dev/null 2>&1") == 0 ? "paplay" : "aplay")
#define CHECKING_SOUND_PATH "assets/checking.wav"
#define VALID_SOUND_PATH "assets/valid.wav"
#define INVALID_SOUND_PATH "assets/invalid.wav"
#define STYLE "%s"
#define VALUE "%c"
#define QUAD_SEPARATOR_RIGHT "%s"
#define QUAD_SEPARATOR_BOTTOM "%s"
#define NEXT_BOARD_LINE "\033[22D\033[1B"

void print_cell(struct SdkPosition *pos, struct Cell *cell) {
    char value = cell->value == 0 ? '.' : cell->value + '0';
    char quad_separator_right[3] = "\0";
    char quad_separator_bottom[42] = "\0";

    if (cell->right) {
        if (cell->pos.col == 2) strcat(quad_separator_right, " |");
    } else if (cell->bottom && cell->pos.row == 2)
        strcat(
            quad_separator_bottom,
            NEXT_BOARD_LINE "-------|-------|-------" NEXT_BOARD_LINE
        );

    printf(
        MOVE_CURSOR_TO STYLE VALUE RESET QUAD_SEPARATOR_RIGHT
            QUAD_SEPARATOR_BOTTOM MOVE_CURSOR_LEFT,
        cell->pos_in_board.y,
        cell->pos_in_board.x,
        cell->style,
        value,
        quad_separator_right,
        quad_separator_bottom
    );
    fflush(stdout);

    if (ticker) {
        if (ticker >= MIN_TICKER_SOUND) {
            pid_t pid = fork();

            if (pid == 0) {
                execlp(
                    AUDIO_COMMAND,
                    AUDIO_COMMAND,
                    strcmp(cell->style, GREEN) == 0     ? VALID_SOUND_PATH
                        : strcmp(cell->style, RED) == 0 ? INVALID_SOUND_PATH
                                                        : CHECKING_SOUND_PATH,
                    (char *)NULL
                );
                exit(EXIT_FAILURE);
            }

            usleep(ticker);
            kill(pid, SIGTERM);
        } else usleep(ticker);
    }
}
