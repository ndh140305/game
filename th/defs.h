#ifndef __DEFS_H
#define __DEFS_H

int score = 0;
int prevScore = 0;
const int radius = 100;
const int SCREEN_WIDTH = 700;
const int MENU_WIDTH = 200;
const int SCREEN_HEIGHT = 700;

const char* WINDOW_TITLE = "test";

const int ENEMY_BULLET_SPEED = 2;

const int PLAYER_WIDTH = 20;
const int PLAYER_HEIGHT = 50;
const int PLAYER_BULLET_SPEED = 7;
const int PLAYER_SPEED = 3;
const int ENEMY_SPEED = 20;

bool END_GAME = false;
bool GAME_START = false;
bool PAUSE = false;
bool COLLISION_ON = true;


int bulletTimer = 0;
const int BULLET_INTERVAL = 500;

#endif // __DEFS_H
