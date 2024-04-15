#ifndef __DEFS_H
#define __DEFS_H

const int radius = 100;
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 700;
const char* WINDOW_TITLE = "test";
const int INTIAL_SPEED = 3;
const int PLAYER_SPEED = 10;
bool END_GAME = false;
bool GAME_START = false;
bool COLLISION_ON = true;


int bulletTimer = 0;
const int BULLET_INTERVAL = 0.1;
int random_x = rand() % SCREEN_WIDTH;
int random_y = rand() % SCREEN_HEIGHT;

#endif // __DEFS_H
