#ifndef __GAME_H
#define	__GAME_H

#include "piece.h"
#include "pit.h"

#define PIT_POS_ROW 1
#define PIT_POS_COL 3

#define MAX_SPEED_LEVEL 10
#define MIN_FALL_SPEED_MS 1000
#define MAX_FALL_SPEED_MS 100

#define GAME_CONTINUE 0
#define GAME_END 1

typedef struct {
    int lines;
    int score;
    int level;
    int fallSpeedMs;
    int timeToMoveDown;
    Piece movingPiece;
    Piece nextPiece;
    int nextPieceId;    
    Pit pit;
} Game;

void start_game(Game *game);

int game_step(Game *game, int elapsedMs, int keyPressed);

void draw_game(Game *game);

int get_game_speed(Game *game);

#endif	/* GAME_H */

