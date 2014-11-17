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
    int c = 0;
    for(y = 1 ; y < get_max_rows() ; y+=4) {
        for(x = 1 ; x < get_max_cols()-5 ; x+=5){
            if(c % 4 == 0) {
                lastPiece = create_random_piece(&p, lastPiece);
            } else {
                rotate_piece(-1,&p);
            }
            p.pCol=x;
            p.pRow=y;
            draw_piece(&p);
            c++;
        }
    }
        
    return 0;
}

