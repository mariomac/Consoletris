#include "piece.h"
#include "pit.h"
#include <stdlib.h>
#include <stdio.h>

static Piece piece_models[NUM_PIECES] = {
    //#define PIECE_BAR       0
    { 0,0,2,0,4,1,COLOR_BAR,{"XXXX"}},
    //#define PIECE_SQUARE    1
    { 0,0,1,1,2,2,COLOR_SQUARE, {
                        "XX",
                        "XX"}},
    //#define PIECE_L         2
    { 0,0,1,0,3,2,COLOR_L, {
                    "  X",
                    "XXX"}},
    //#define PIECE_REVERSE_L 3
    { 0,0,1,0,3,2,COLOR_REVERSE_L, {
                    "XXX",
                    "  X"}},                        
    //#define PIECE_T         4
    { 0,0,1,0,3,2,COLOR_T, {
                    " X ",
                    "XXX"}},
    //PIECE_S
    { 0,0,1,0,3,2,COLOR_S, {
                        " XX","XX "}},
    //PIECE_REVERSE_S
    { 0,0,1,0,3,2,COLOR_REVERSE_S, {
                        "XX "," XX"}},
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
void draw_piece(int or, int oc, Piece *piece) {
    int c,r;
    set_background(piece->color);
    for(c = 0 ; c < piece->nCols ; c++) {
        for(r = 0 ; r < piece->nRows ; r++) {
            if(piece->blocks[r][c] != ' ') {
                set_position(or+piece->pRow+piece->offRow+r,oc+piece->pCol+piece->offCol+c);
                putchar(' ');
            }
        }
    }
    set_background(BLACK);
}

void rotate_piece(int direction, Piece *piece) {
    char tmp;
    int x,y,t,dx,dy;
    int cos,sin;
    if(direction > 0) {
        sin = 1;
        cos = 0;
    } else {
        sin = -1;
        cos = 0;
    }
            
    int s = piece->nCols > piece->nRows ? piece->nCols : piece->nRows;
    
    Piece src = *piece;
    for(x = 0 ; x < piece->nCols ; x++) {
        for(y = 0 ; y < piece->nRows ; y++) {
            if(direction > 0) {
                piece->blocks[x][piece->nRows-1-y] = src.blocks[y][x];
            } else {
                piece->blocks[piece->nCols-1-x][y] = src.blocks[y][x];
            }
        }               
    }
    piece->nCols = src.nRows;
    piece->nRows = src.nCols;
    piece->offCol = src.offRow;
    piece->offRow = src.offCol;
}

