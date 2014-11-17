#include "pit.h"
#include "betterconsole.h"
#include "piece.h"

void clear_pit(Pit *pit) {
    int r,c;
    for(r = 0 ; r < PIT_ROWS ; r++) {
        for(c = 0 ; c < PIT_COLUMNS ; c++) {
            pit->blocks[r][c] = BLACK;
        }
    }
}

int can_move(Pit *pit, Piece *piece, int rowInc, int colInc) {
    int r,c;
    for(r = 0 ; r < piece->nRows ; r++ ) {
        for(c = 0 ; c < piece->nCols ; r++) {
            if(piece->blocks[r][c] != ' ') {
                int nextCol = piece->pCol+piece->offCol+colInc;
                int nextRow = piece->pRow+piece->offRow+rowInc;
                if(nextCol < 0 || nextCol >= PIT_COLUMNS
                   || nextRow >= PIT_ROWS
                   || pit->blocks[nextRow][nextCol] != BG_COLOR) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void draw_pit(Pit *pit, Piece *movingPiece) {
    int r,c;
    // draw pit
    for(r = PIT_HIDDEN_ROWS ; r < PIT_ROWS ; r++) {
        for(c = 0 ; c < PIT_COLUMNS ; c++ ) {
            set_position(r+PIT_POS_ROW-PIT_HIDDEN_ROWS,c+PIT_POS_COL);
            set_background(pit->blocks[r][c]);
            putchar(' ');
        }        
    }
    // draw pit margins
    set_background(PIT_MARGIN_COLOR);
    for(r = 0 ; r < PIT_ROWS-PIT_HIDDEN_ROWS ; r++) {
        set_position(r+PIT_POS_ROW,PIT_POS_COL-1);
        putchar(' ');
        set_position(r+PIT_POS_ROW,PIT_POS_COL+PIT_COLUMNS);
        putchar(' ');        
    }
    for(c = -1 ; c <= PIT_COLUMNS ; c++) {
        set_position(PIT_POS_ROW + PIT_ROWS - PIT_HIDDEN_ROWS, PIT_POS_COL + c );
        putchar(' ');
    }  
    // draw moving piece
    draw_piece(PIT_POS_ROW - PIT_HIDDEN_ROWS, PIT_POS_COL, movingPiece);
}




