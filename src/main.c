/* 
 * File:   examples.c
 * Author: mmacias
 *
 * Created on 13 de noviembre de 2014, 20:09
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "piece.h"
#include "betterconsole.h"
#include "pit.h"

int main() {
    clear_screen();
    Pit pit;
    clear_pit(&pit);
    Piece piece;
    create_random_piece(&piece,-1);
    piece.pCol = (PIT_COLUMNS-PIECE_MAX_SIDE)/2;
    piece.pRow = 0;
    
    draw_pit(&pit,&piece);
            
    return 0;
}

