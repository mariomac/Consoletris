#ifndef __PIECE_H
#define	__PIECE_H

#include "betterconsole.h"

#define PIECE_MAX_SIDE 4

#define PIECE_BAR       0
#define PIECE_SQUARE    1
#define PIECE_L         2
#define PIECE_REVERSE_L 3
#define PIECE_T         4
#define PIECE_S         5
#define PIECE_INVERSE_S 6
#define NUM_PIECES      7

// Original Alexey Pajitnov color set
#define COLOR_BAR       RED
#define COLOR_SQUARE    BLUE
#define COLOR_L         MAGENTA
#define COLOR_REVERSE_L WHITE
#define COLOR_T         BROWN
#define COLOR_S         GREEN
#define COLOR_REVERSE_S CYAN

typedef struct {
    int pRow;  // position
    int pCol;
    int offRow; //offsets for drawing it
    int offCol;
    int nCols;  // size of the rotated piece
    int nRows;
    int color;
    char blocks[PIECE_MAX_SIDE][PIECE_MAX_SIDE];
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
void rotate_piece(int direction, Piece *piece);

/**
 * 
 * @param or the origin of the row coordinates, in screen
 * @param oc the origin of the column coordinates, in screen
 * @param piece
 */
void draw_piece(int or, int oc, Piece *piece);

#endif	/* __PIECE_H */

