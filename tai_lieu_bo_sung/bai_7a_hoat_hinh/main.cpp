#include "graphics.h"
#include "defs.h"
#include "game.h"
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
    Mouse mouse;
    mouse.x = SCREEN_WIDTH / 2;
    mouse.y = SCREEN_HEIGHT / 2;

    Graphics graphics;
    graphics.init();

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        //Handle events on queue
        while (!quit && !gameOver(mouse)) {


        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_UP]) mouse.turnNorth();
        if (currentKeyStates[SDL_SCANCODE_DOWN]) mouse.turnSouth();
        if (currentKeyStates[SDL_SCANCODE_LEFT]) mouse.turnWest();
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) mouse.turnEast();

        mouse.move();
        render(mouse, graphics);

        graphics.presentScene();
        SDL_Delay(10);
    }

    }

    graphics.quit();
    return 0;


}
