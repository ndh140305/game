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

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_UP] ) cerr << " Up";
        if (currentKeyStates[SDL_SCANCODE_DOWN] ) cerr << " Down";
        if (currentKeyStates[SDL_SCANCODE_LEFT] ) cerr << " Left";
        if (currentKeyStates[SDL_SCANCODE_RIGHT] ) cerr << " Right";
        if (currentKeyStates[SDL_SCANCODE_3]) cerr << "3";
        if (currentKeyStates[SDL_SCANCODE_5]) cerr << "5";
        if (currentKeyStates[SDL_SCANCODE_4]) cerr << "4";
        if (currentKeyStates[SDL_SCANCODE_2]) cerr << "2";
        cerr << ".\n";

        SDL_Delay(100);
    }

    graphics.quit();
    return 0;


}
