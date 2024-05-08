#include "graphics.h"
#include "defs.h"
#include <bits/stdc++.h>
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

    Mix_Music *gMusic = graphics.loadMusic ("SFF.mp3");
    Mix_Chunk *gJump = graphics.loadSound("rain-01.wav");
    graphics.play(gMusic);
    graphics.play(gJump);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);


        SDL_Delay(10);
    }
    if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    if (gJump != nullptr) Mix_FreeChunk( gJump);
    graphics.quit();
    return 0;


}
