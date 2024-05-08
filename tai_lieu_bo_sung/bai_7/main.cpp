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
int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("Screenshot 2024-04-08 152712.png"));

    bool quit = false;
    SDL_Event e;
    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
        }

        background.scroll(1);

        graphics.render(background);

        graphics.presentScene();
        SDL_Delay(100);
    }

    SDL_DestroyTexture( background.texture );
    graphics.quit();
    return 0;


    graphics.quit();
    return 0;

}
