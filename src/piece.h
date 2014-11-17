#ifndef __PIECE_H
#define	__PIECE_H

#include "betterconsole.h"

#define MAX_SIDE 4

#define PIECE_BAR       0
#define PIECE_SQUARE    1
#define PIECE_L         2
#define PIECE_REVERSE_L 3
#define PIECE_T         4
#define NUM_PIECES      5

#define COLOR_BAR       RED+BRIGHT
#define COLOR_SQUARE    BLUE+BRIGHT
#define COLOR_L         GREEN+BRIGHT
#define COLOR_REVERSE_L MAGENTA+BRIGHT
#define COLOR_T         CYAN+BRIGHT

typedef struct {
    int pRow;
    int pCol;
    int width;
    int height;
    int color;
    char blocks[MAX_SIDE][MAX_SIDE];
} Piece;

/**
 * 
 * @param piece
 * @param exclude ID of piece to be excluded from the results (to avoid repeating twice
 * the same piece). -1 if you allow repeating pieces
 * @return the ID of the created piece
 */
int create_random_piece(Piece *piece, int exclude);

/**
 * 
 * @param direction direction<0 rotates counterclockwise, direction>=0 rotates clockwise
 * @param piece
 */

void draw_piece(Piece *piece);

#endif	/* __PIECE_H */

