#ifndef PIECE_H
#define	PIECE_H

#define MAX_SIDE 4

#define PIECE_BAR       0
#define PIECE_SQUARE    1
#define PIECE_L         2
#define PIECE_REVERSE_L 3
#define PIECE_T         4
#define NUM_PIECES      5

typedef struct {
    int posX;
    int posY;
    int width;
    int height;
    int color;
    char draw[MAX_SIDE][MAX_SIDE];
} Piece;


Piece create_piece(int numPiece);

void rotate_piece(int )

#endif	/* PIECE_H */

