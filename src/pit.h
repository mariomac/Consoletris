#ifndef __PIT_H
#define	__PIT_H

#include "betterconsole.h"
#include "piece.h"

#define BG_COLOR BLACK

#define PIT_COLUMNS 10
#define PIT_ROWS 22
#define PIT_HIDDEN_ROWS 2

#define PIT_MARGIN_COLOR WHITE+BRIGHT

typedef struct {
    char blocks[PIT_ROWS][PIT_COLUMNS]; //stores the color of the block. 0 (BG_COLOR) means void cell
} Pit;

/**
 * clears the entire pit. Puts its values to 0
 * @param pit
 */
void clear_pit(Pit *pit);
/**
 * Checks if the piece, according to its current position, can move to the 
 * relative position (+rowInc,+colInc). It also checks if it can rotate (if rotation != 0)
 * 
 * @param pit
 * @param piece
 * @param rowInc
 * @param colInc
 * @return 0 if can not move, != 0 if can move
 */
int can_move(Pit *pit, Piece *piece, int rowInc, int colInc, int rotation);

void consolidate_piece(Pit *pit, Piece *piece);

void draw_pit(int topRow, int leftCol, Pit *pit);

#endif	/* __PIT_H */

