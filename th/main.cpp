#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <bits/stdc++.h>

#include "defs.h"
#include "object.h"
#include "graphics.h"


using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}


int main(int argc , char* argv[])
{
    Graphics graphics;
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);

    Player player;

    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music* music = graphics.loadMusic("SFF.mp3");
    graphics.play(music);

    vector<round_bullet> bullets1;
    for (int i = 0; i < 30; ++i) {
        bullets1.push_back(round_bullet(i * 20, i * 20 , 10.0*i));
        bullets1.back().load_bullet(renderer);
    }

    vector<round_bullet> bullets2;
    for (int i = 0; i < 30; ++i) {
        bullets1.push_back(round_bullet(SCREEN_WIDTH - i * 20, i * 20 , 10.0*i));
        bullets1.back().load_bullet(renderer);
    }

    vector<round_bullet> bullets3 = createBullets(rand()%100, random_x, random_y, 1.0 * rand(), renderer);
    vector<round_bullet> bullets4 = createSpreadBullets(100, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, renderer);


    vector<round_bullet> bullets;
    for (double angle = 0; angle < 2 * M_PI; angle += 2 * M_PI / 10) {
        bullets.push_back(round_bullet(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, angle));
        bullets.back().load_bullet(renderer);
    }

    waitUntilKeyPressed();
    SDL_Event e;
    while (!END_GAME) {
        if ( SDL_PollEvent(&e) != 0 && (e.type == SDL_QUIT) ){
                 break;
             }
        SDL_RenderClear(renderer);
        load_background(renderer);
        player.load_player(renderer);

        if (!GAME_START)
        {
            SDL_RenderPresent(renderer);
            waitUntilKeyPressed();
            GAME_START = true;
        }

        player.keyboard_movement(e);

        //shootBullets(bullets3, player, renderer, END_GAME);
        shootBullets(bullets4, player, renderer, END_GAME);

       bulletTimer++;

        if (bulletTimer >= BULLET_INTERVAL)
        {
             bullets3.push_back(round_bullet(rand() % SCREEN_WIDTH, 0 , (1*rand())%45 + 45));
             bullets3.back().draw_bullet(renderer);
             bulletTimer = 0;
        }
        shootBullets(bullets3, player, renderer, END_GAME);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);

    }
    if (music != nullptr) Mix_FreeMusic( music );
    cerr << "You lose! What a noob.";
}
