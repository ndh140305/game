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

    SDL_Event event;
    int x, y;
    while (1) {
        SDL_GetMouseState(&x, &y);
        cout << x << ", " << y << endl;

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
        }
        SDL_Delay(100);
    }

    graphics.quit();
    return 0;


}
