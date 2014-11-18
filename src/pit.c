#include "pit.h"
#include "betterconsole.h"
#include "piece.h"
#include <stdio.h>

void clear_pit(Pit *pit) {
    int r,c;
    for(r = 0 ; r < PIT_ROWS ; r++) {
        for(c = 0 ; c < PIT_COLUMNS ; c++) {
            pit->blocks[r][c] = BLACK;
        }
    }
}

int can_move(Pit *pit, Piece *piece, int rowInc, int colInc, int rotation) {
    int r,c;
    Piece tst = *piece;
    
    if(rotation != 0) {
        rotate_piece(rotation, &tst);
    }

    for(r = 0 ; r < tst.nRows ; r++ ) {
        for(c = 0 ; c < tst.nCols ; c++) {
            if(tst.blocks[r][c] != ' ') {
                int nextCol = tst.pCol+tst.offCol+colInc;
                int nextRow = tst.pRow+tst.offRow+rowInc;
                if(nextCol < 0 || nextCol >= PIT_COLUMNS
                   || nextRow >= PIT_ROWS
                   || tst.blocks[nextRow][nextCol] != BG_COLOR) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void consolidate_piece(Pit *pit, Piece *piece) {
    int r,c;
    for(r = 0 ; r < piece->nRows ; r++) {
        for(c = 0 ; c < piece->nCols ; c++) {
            if(piece->blocks[r][c] != ' ') {
                pit->blocks[piece->pRow+piece->offRow+r][piece->pCol+piece->offCol+c] = piece->color;
            }
        }
    }
} 

void draw_pit(int topRow, int leftCol, Pit *pit) {
    int r,c;
    // draw pit
    for(r = PIT_HIDDEN_ROWS ; r < PIT_ROWS ; r++) {
        for(c = 0 ; c < PIT_COLUMNS ; c++ ) {
            set_position(r+topRow-PIT_HIDDEN_ROWS,c+leftCol);
            set_background(pit->blocks[r][c]);
            putchar(' ');
        }        
    }
    // draw pit margins
    set_background(PIT_MARGIN_COLOR);
    for(r = 0 ; r < PIT_ROWS-PIT_HIDDEN_ROWS ; r++) {
        set_position(r+topRow,leftCol-1);
        putchar(' ');
        set_position(r+topRow,leftCol+PIT_COLUMNS);
        putchar(' ');        
    }
    for(c = -1 ; c <= PIT_COLUMNS ; c++) {
        set_position(topRow + PIT_ROWS - PIT_HIDDEN_ROWS, leftCol + c  );
        putchar(' ');
    }  
}




