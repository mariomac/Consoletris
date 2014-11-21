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

#define STATUS_START_SCREEN 0
#define STATUS_GAME 1
#define STATUS_GAME_OVER 2
#define STATUS_CONFIRM_EXIT 3
#define STATUS_END 4

void print_confirm_exit() {
    int rpos = (get_max_rows()-4)/2;
    int cpos = (get_max_cols()-23)/2; 
    set_background(WHITE);
    set_foreground(BLACK);
    
    set_position(rpos,cpos); printf("***********************");
    set_position(rpos+1,cpos); printf("* Do you  really want *");
    set_position(rpos+2,cpos); printf("*    to exit? (Y/N)   *"); 
    set_position(rpos+3,cpos); printf("***********************");
}

int main_game_loop(Game *theGame, int keyPressed) {
    int cont = game_step(theGame, 50, keyPressed);
    draw_game(theGame);
    set_position(18, 20);
    printf("Lines: %d   ", theGame->lines);
    set_position(19, 20);
    printf("Level: %d                       ", theGame->level);
    set_position(20, 20);
    printf("Speed: %d                       ", get_game_speed(theGame));
    return cont;
}

void show_game_over() {
    int rpos = (get_max_rows()-13)/2;
    int cpos = (get_max_cols()-23)/2; 
    set_background(BLUE);
    set_foreground(WHITE+BRIGHT);

    set_position(rpos,cpos);   printf("+-----------+");
    set_position(rpos+1,cpos); printf("| GAME_OVER |");
    set_position(rpos+2,cpos); printf("+-----------+");
}

void show_start_screen() {
    int r,c;
    char txt[8][57] = {
        "                                                         ",
        "  WWW  WWW  W  W  WWW   WWW  W    WWWW WWW WWW  W  WWW   ",
        " W    W   W WW W W     W   W W    W     W  W  W W W      ",
        " W    W   W W WW  WWW  W   W W    WWW   W  WWW  W  WWW   ",
        " W    W   W W  W     W W   W W    W     W  W  W W     W  ",
        "  WWW  WWW  W  W  WWW   WWW  WWWW WWWW  W  W  W W  WWW   ",
        "                                                         ",
        "                                                         "
        
    };
    int r1 = 3,c1 = 10;
    double bright;
    for(r = 0 ; r < 8 ; r++) {
        for(c = 0 ; c < 57 ; c++) {
           
            set_position(r+r1,c+c1);
            if(txt[r][c] == 'W') {
                set_background(rgb(1.08-0.08*r,0.5,0.08*r));
                putchar(' ');
                
            } else {
                bright = 0.5;
                if(r > 0 && txt[r-1][c] == 'W') {
                    bright -= 0.15;
                }
                if(c > 0 && txt[r][c-1] == 'W') {
                    bright -= 0.15;
                }
                if(c > 0 && r > 0 && txt[r-1][c-1] == 'W') {
                    bright -= 0.15;
                }
                set_background(gray(bright));
                putchar(' ');                
            }

           
        }
    }
    set_background(BLACK);
    set_foreground(WHITE);
    set_position(16,20); printf("Press RETURN to start game");
    set_position(18,24); printf("Press ESC to exit");
}

int main() {
    clear_screen();
    echo_off();
    cursor_off();
    set_background(BLACK);

    int status = STATUS_START_SCREEN;
    int lastStatus;
    
    Game theGame;

    int keyPressed = 0;
    int cont = GAME_CONTINUE;
    
    do {
        keyPressed = get_key_pressed();
        if(keyPressed == KEY_ESC) {
            lastStatus = status;
            status = STATUS_CONFIRM_EXIT;
            keyPressed = NO_KEY;
        }
        
        switch(status) {
            case STATUS_START_SCREEN:
                show_start_screen();
                if(keyPressed == '\n') {
                    status = STATUS_GAME;
                    start_game(&theGame);

                }
                break;
            case STATUS_CONFIRM_EXIT:
                print_confirm_exit();
                if(keyPressed == 'y' || keyPressed == 'Y') {
                    status = STATUS_END;
                } else if(keyPressed != NO_KEY) {
                    status = lastStatus;
                }
                break;
            case STATUS_GAME:
                cont = main_game_loop(&theGame, keyPressed);
                if(cont == GAME_END) {
                    status = STATUS_GAME_OVER;
                    keyPressed = NO_KEY;

                }
                break;
            case STATUS_GAME_OVER:
                show_game_over();
                if(keyPressed != NO_KEY) {
                    set_background(BLACK);
                    clear_screen();
                    status = STATUS_START_SCREEN; 
                }
                break;
        }      
        
        
        fflush(stdout);
        //empty_keyboard_buffer();
        usleep(50000);
    } while (status != STATUS_END);

    set_background(BLACK);
    set_foreground(WHITE);
    echo_on();
    cursor_on();
    set_position(1,1);
    clear_screen();

    return 0;
}

