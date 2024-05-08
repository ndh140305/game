#include "defs.h"
#include "object.h"
#include "graphics.h"
#include "sounds.h"
#include "background.h"
#include "menu.h"
using namespace std;

int main(int argc , char* argv[])
{
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    ScrollingBackground bg = create_bg(renderer);
    vector<Button> menu = create_menu(renderer);
    Player player;
    Enemy enemy;
    player.load_texture(renderer);
    enemy.load_texture(renderer);
    load_BGM();

    vector<round_bullet> bullets = createSpreadBullets (enemy.hitbox.x , enemy.hitbox.y , renderer);
    waitUntilKeyPressed();
    SDL_Event e;
    while (!END_GAME)
    {
        if ( SDL_PollEvent (&e) == 0 && e.type == SDL_QUIT )
        {
            break;
        }

        if (!PAUSE)
        {
            load_bg(renderer , bg);
            enemy.render(renderer);
            enemy.movement(rand()%4);

            shoot_bullets(bullets , player , renderer);
            player.load(renderer , enemy);

            bulletTimer++;
            if (bulletTimer >= BULLET_INTERVAL)
            {
                reload_bullets(enemy.hitbox.x , enemy.hitbox.y , bullets);
                bulletTimer = 0;
            }
        }

        show_menu(menu , renderer);
        click_button(e , menu , player , enemy , bullets);

        SDL_RenderPresent(renderer);
    }
    quit(renderer , window);
    return 0;
}
