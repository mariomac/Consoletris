#include "game.h"
#include "betterconsole.h"
#include <stdio.h>

void get_new_piece(Game *game) {
    game->movingPiece = game->nextPiece;
    game->movingPiece.pCol = (PIT_COLUMNS - PIECE_MAX_SIDE) / 2;
    game->nextPieceId = create_random_piece(&game->nextPiece,game->nextPieceId);    
}

void start_game(Game *game) {
    game->score = 0;
    game->nextPieceId = -1;
    get_new_piece(game);   // 
    get_new_piece(game);    
    clear_pit(&game->pit);
}

void draw_game(Game *game) {
    draw_pit(PIT_POS_ROW, PIT_POS_COL, &game->pit);
    draw_piece(PIT_POS_ROW - PIT_HIDDEN_ROWS, PIT_POS_COL, &game->movingPiece);
    
    // todo: use constants,
    draw_piece(PIT_POS_ROW + 2, PIT_POS_COL + PIT_COLUMNS + 5, &game->nextPiece);
}

void game_step(Game *game, int elapsedMs, const int keyPressed) {    
    int rowInc = 0, colInc = 0, rotation = 0;
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
            rowInc = 1;
            break;
    }
    if((rowInc != 0 || colInc != 0 || rotation != 0)
            && can_move(&(game->pit),&(game->movingPiece),rowInc,colInc,rotation)) {
        game->movingPiece.pRow += rowInc;
        game->movingPiece.pCol += colInc;
        if (rotation != 0) {
            rotate_piece(rotation, &game->movingPiece);
        }
    }
    if(!can_move(&game->pit,&game->movingPiece,1,0,0)) {
        consolidate_piece(&game->pit,&game->movingPiece);
        get_new_piece(game);
    }
}


