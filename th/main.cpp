#include "defs.h"
#include "object.h"
#include "graphics.h"
#include "sounds.h"
#include "background.h"
#include "sprite.h"
#include "logic.h"

using namespace std;

int main(int argc , char* argv[])
{
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);
    ScrollingBackground bg = create_bg(renderer);
    Player player;
    Enemy enemy (400 , 100);
    player.load_texture(renderer);
    enemy.load_texture(renderer);
    load_BGM();
    load_sprite(renderer);
    vector<round_bullet> bullets = createSpreadBullets (SCREEN_WIDTH/2 , SCREEN_HEIGHT/5 , renderer);
    vector<round_bullet> bullets1 = createFastBullets (SCREEN_WIDTH/2 , SCREEN_HEIGHT/5 , renderer , player.hitbox.x , player.hitbox.y);
    waitUntilKeyPressed();
    SDL_Event e;
    while (!END_GAME) {
        if ( SDL_PollEvent(&e) != 0 && e.type == SDL_QUIT ){
                 break;
             }
        load_bg(renderer , bg);
        player.load(renderer);
        enemy.render(renderer);
        enemy.movement(rand()%4);
        bulletTimer++;

        shootBullets(bullets , player , renderer);
        if (bulletTimer >= BULLET_INTERVAL)
        {
            reloadBullets(enemy.hitbox.x , enemy.hitbox.y , bullets);
            bulletTimer = 0;
        }
        SDL_RenderPresent(renderer);
    }
    cerr << "You lose! What a noob.";
    quit(renderer , window);
    return 0;
}
