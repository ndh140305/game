#ifndef __DEFS_H
#define __DEFS_H

const int radius = 100;
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;

const char* WINDOW_TITLE = "test";

const int INTIAL_SPEED = 5;
const int PLAYER_SPEED = 5;
const int ENEMY_SPEED = 10;

bool END_GAME = false;
bool GAME_START = false;
bool COLLISION_ON = false;


int bulletTimer = 0;
const int BULLET_INTERVAL = 10;

const int MOVES[][4] = {
    {2, 47, 20, 45},
    {22, 47, 20, 45},
    {42, 47, 20, 45},
    {62, 47, 20, 45},
    {82, 47, 20, 45},
    {102, 47, 20, 45},
    {122, 47, 20, 45},
    {142, 47, 20, 45},
};

const int FRAMES = sizeof(MOVES)/sizeof(int)/4;
#endif // __DEFS_H
