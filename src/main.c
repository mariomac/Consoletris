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
    echo_off();
    cursor_off();

    Game theGame;
    start_game(&theGame);

    int keyPressed = 0, nzkey;
    
    do {
        keyPressed = get_key_pressed();
        //        do {
        //            nzkey = get_key_pressed();
        //            if(nzkey != 0) {
        //                keyPressed = nzkey;
        //            }
        //        } while(nzkey != 0);

        game_step(&theGame, 50, keyPressed);
        draw_game(&theGame);
        set_position(18,20); printf("%d                       ", keyPressed);        
        fflush(stdout);
        //empty_keyboard_buffer();
        usleep(50000);
    } while (keyPressed != KEY_ESC);

    echo_on();
    cursor_on();
    clear_screen();

    return 0;
}

