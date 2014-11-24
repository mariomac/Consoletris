#include "game.h"
#include "betterconsole.h"
#include <stdio.h>

void get_new_piece(Game *game) {
    game->movingPiece = game->nextPiece;
    game->movingPiece.pCol = (PIT_COLUMNS - PIECE_MAX_SIDE) / 2;
    game->nextPieceId = create_random_piece(&game->nextPiece,game->nextPieceId);    
    game->timeToMoveDown = get_game_speed(game);
}

void start_game(Game *game) {
    game->lines = 0;
    game->score = 0;
    game->nextPieceId = -1;
    game->level = 1;
    get_new_piece(game);   // 
    get_new_piece(game);    
    clear_pit(&game->pit);
}

void draw_game(Game *game) {
    
    double r,c;
    set_position(1,1);
    for(r = 0 ; r < CONSOLE_ROWS ; r++) {
        for(c = 0 ; c < CONSOLE_COLUMNS ; c++) {
            set_background(gray((r+c)/(CONSOLE_ROWS+CONSOLE_COLUMNS)));
            putchar(' ');
        }
        putchar('\n');
    }
    
    draw_pit(PIT_POS_ROW, PIT_POS_COL, &game->pit);
    draw_piece(PIT_POS_ROW - PIT_HIDDEN_ROWS, PIT_POS_COL, &game->movingPiece);
    
    // todo: use constants,
    draw_piece(PIT_POS_ROW + 2, PIT_POS_COL + PIT_COLUMNS + 5, &game->nextPiece);
}

int get_game_speed(Game *game) {
    if(game->level > MAX_SPEED_LEVEL) {
        return MAX_FALL_SPEED_MS;
    } else {
        return MAX_FALL_SPEED_MS + ((MIN_FALL_SPEED_MS - MAX_FALL_SPEED_MS) * (MAX_SPEED_LEVEL - (game->level - 1)))/MAX_SPEED_LEVEL;
    }
}

/**
 * removes complete lines
 * @param game
 * @return the number of removed lines
 */
int check_lines(Game *game) {
    int linesToRemove = 0;
    int lineBlocks;
    int r,c;
    for(r = PIT_ROWS - 1 ; r>=PIT_HIDDEN_ROWS ; r-- ) {
        lineBlocks = 0;
        for(c = 0 ; c < PIT_COLUMNS ; c++) {
            if(linesToRemove > 0) {
                game->pit.blocks[r+linesToRemove][c] = game->pit.blocks[r][c];
            }
            if(game->pit.blocks[r][c] != BG_COLOR) {
                lineBlocks++;
            }
        }
        if(lineBlocks == c) {
            linesToRemove++;
        }
    }
    
    return linesToRemove;  
}

int game_step(Game *game, int elapsedMs, const int keyPressed) {    
    int colInc = 0, rotation = 0;
    game -> timeToMoveDown -= elapsedMs;
    switch(keyPressed) {
        case KEY_LEFT:
            colInc = -1;
            break;
        case KEY_RIGHT:
            colInc = 1;
            break;
        case KEY_UP:
            rotation = -1;
            break;
        case KEY_DOWN:
            game->timeToMoveDown = 0;
            break;
        case 'l':
            game->level++;
            break;
    }
    // checks if it can move horizontally or rotate
    if((colInc != 0 || rotation != 0)
            && can_move(&(game->pit),&(game->movingPiece),0,colInc,rotation)) {
        game->movingPiece.pCol += colInc;
        if (rotation != 0) {
            rotate_piece(rotation, &game->movingPiece);
        }
    }
    // checks if it has to move down and/or consolidate
    if(game->timeToMoveDown <= 0) {
        game->timeToMoveDown = get_game_speed(game);
        if(can_move(&game->pit,&game->movingPiece,1,0,0)) {
            game->movingPiece.pRow++;
        } else {
            consolidate_piece(&game->pit,&game->movingPiece);
            game->lines += check_lines(game);
            get_new_piece(game);
            int cm = can_move(&game->pit,&game->movingPiece,0,0,0);
            if(cm == 0) {
                return GAME_END;
            }
        }
    }
    return GAME_CONTINUE;
}


