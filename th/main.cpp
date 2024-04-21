#include "defs.h"
#include "object.h"
#include "graphics.h"
#include "sounds.h"
#include "background.h"
#include "sprite.h"

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
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);

    ScrollingBackground bg = create_bg(renderer);

    Player player;
    Enemy enemy (400 , 100);
    load_BGM();
    load_sprite(renderer);

    vector<round_bullet> bullets = createBullets(10 , rand() % SCREEN_WIDTH , rand() % SCREEN_HEIGHT , rand() % 90 + 45 , renderer);
    waitUntilKeyPressed();
    SDL_Event e;
    while (!END_GAME) {
        if ( SDL_PollEvent(&e) != 0 && e.type == SDL_QUIT ){
                 break;
             }
        load_bg(renderer , bg);
        player.load(renderer);
        enemy.load_enemy(renderer);
        enemy.movement(rand()%4);
       bulletTimer++;

        if (bulletTimer >= BULLET_INTERVAL)
        {
             /*bullets.push_back(round_bullet(rand() % SCREEN_WIDTH, 0 , (1*rand())%45 + 45));
             bullets.back().load_bullet(renderer , 0);
             bullets.push_back(round_bullet(rand() % SCREEN_WIDTH, 350 , (1*rand())%45 + 45));
             bullets.back().load_bullet(renderer , 0);
             bulletTimer = 0;*/
        }

        //shootBullets(bullets , player , renderer);

        SDL_RenderPresent(renderer);
    }
    cerr << "You lose! What a noob.";
    quit(renderer , window);
    return 0;
}
