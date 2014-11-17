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

int main() {
    clear_screen();
    int x,y,lastPiece = -1;
    Piece p;
    for(y = 1 ; y < get_max_rows() ; y+=3) {
        for(x = 1 ; x < get_max_cols()-5 ; x+=5){
            lastPiece = create_random_piece(&p, lastPiece);
            p.pCol=x;
            p.pRow=y;
            draw_piece(&p);
        }
    }
        
    return 0;
}

