#ifndef TERM_ACTIONS
#define TERM_ACTIONS

#define MOVE_CURSOR_TO "\033[%d;%dH"
#define MOVE_CURSOR_LEFT "\033[D"
#define MOVE_CURSOR_RIGHT "\033[C"
#define CURSOR_INVISIBLE "\033[?25l"
#define CURSOR_VISIBLE "\033[?25h"
#define CLEAR "\033[2J"
#define RESET "\033[0m"
#define RESET_ALL "\033[0m\033[39m\033[49m\033[0 q"

#endif
