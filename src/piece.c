#include "piece.h"
#include "pit.h"
#include <stdlib.h>
#include <stdio.h>

static Piece piece_models[NUM_PIECES] = {
    //#define PIECE_BAR       0
    { 0,0,4,1,COLOR_BAR,{"XXXX"}},
    //#define PIECE_SQUARE    1
    { 0,0,2,2,COLOR_SQUARE, {
                        "XX",
                        "XX"}},
    //#define PIECE_L         2
    { 0,0,3,2,COLOR_L, {
                    "  X",
                    "XXX"}},
    //#define PIECE_REVERSE_L 3
    { 0,0,3,2,COLOR_REVERSE_L, {
                    "XXX",
                    "  X"}},                        
    //#define PIECE_T         4
    { 0,0,3,2,COLOR_T, {
                    " X ",
                    "XXX"}},
};
int create_random_piece(Piece *piece, int exclude) {
    int numPiece;
    
    do {
        numPiece = arc4random_uniform(NUM_PIECES);
    } while(numPiece == exclude);

    *piece = piece_models[numPiece];    
    return numPiece;
}

// TODO: que no se repitan las piezas
void draw_piece(Piece *piece) {
    int c,r;
    set_background(piece->color);
    for(c = 0 ; c < piece->width ; c++) {
        for(r = 0 ; r < piece->height ; r++) {
            if(piece->blocks[r][c] != ' ') {
                set_position(piece->pRow+r,piece->pCol+c);
                putchar(' ');
            }
        }
    }
    set_background(BLACK);
}

