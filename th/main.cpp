#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <bits/stdc++.h>

#include "defs.h"
#include "sounds.h"
#include "object.h"
#include "graphics.h"

using namespace std;

int main(int argc , char* argv[])
{
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);

    Player player;

    Mix_Music* music = loadMusic("SFF.mp3");
    play(music);

    vector<round_bullet> bullets1;
    for (int i = 0; i < 10; ++i) {
        bullets1.push_back(round_bullet(i * 20, i * 20 , 5));
        bullets1.back().load_bullet(renderer);
    }

    vector<round_bullet> bullets2;
    for (int i = 0; i < 10; ++i) {
        bullets2.push_back(round_bullet(SCREEN_WIDTH - i * 20,i * 20 , -5 ));
        bullets2.back().load_bullet(renderer);
    }


    vector<round_bullet> bullets;
    for (double angle = 0; angle < 2 * M_PI; angle += 2 * M_PI / 10) {
        bullets.push_back(round_bullet(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, angle));
        bullets.back().load_bullet(renderer);
    }

    vector<vector<round_bullet>> bullets3;
    for (int i = 0; i < 10; ++i) {
        bullets3.push_back(vector<round_bullet>());
    for (double angle = 0; angle < 2 * M_PI; angle += 2 * M_PI / 10) {
        bullets3[i].push_back(round_bullet(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, angle + i * 2 * M_PI / 100));
        bullets3[i].back().load_bullet(renderer);
    }
}

    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) ){
                 break;
             }
        SDL_RenderClear(renderer);
        load_background(renderer);
        player.load_player(renderer);
        player.mouse_movement(e);
        for (auto& bullet: bullets){
            bullet.move();
            SDL_RenderCopy(renderer , bullet.texture , NULL , &bullet.hitbox);
            if (player.check_collision(bullet))
            {
                break;
            }
        }
        for (auto& bullet: bullets1){
            bullet.move();
            SDL_RenderCopy(renderer , bullet.texture , NULL , &bullet.hitbox);
            if (player.check_collision(bullet))
            {
                break;
            }
        }
        for (auto& bullet: bullets2){
            bullet.move();
            SDL_RenderCopy(renderer , bullet.texture , NULL , &bullet.hitbox);
            if (player.check_collision(bullet))
            {
                break;
            }
        }
        SDL_RenderPresent(renderer);


        SDL_Delay(10);

    }
    if (music != nullptr) Mix_FreeMusic( music );
    bullets3.clear();

}
