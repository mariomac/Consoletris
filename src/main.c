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
#include "game.h"

int main() {
    clear_screen();
    
    Game theGame;
    start_game(&theGame);
    
    draw_game(&theGame);
    
            
    return 0;
}

