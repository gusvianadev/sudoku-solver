#ifndef QUAD_POS
#define QUAD_POS
#include "u_t.h"

/**
 * | [] | [] | [] | <- row0
 *
 * | [] | [] | [] | <- row1
 *
 * | [] | [] | [] | <- row2
 */
u8 quad_row(u8 quad); 

/**
 * |col0|col1|col2|
 *
 * | [] | [] | [] |
 *
 * | [] | [] | [] |
 *
 * | [] | [] | [] |
 */
u8 quad_col(u8 quad); 

#endif
