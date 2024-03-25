#include "graphics.h"
#include "defs.h"
#include "logic.h"
#include <bits/stdc++.h>
using namespace std;

void processClick(int x, int y, Tictactoe& game) {
    // chuyển tọa độ màn hình x, y thành tọa độ hàng cột của game
    int clickedCol = (x - BOARD_X) / CELL_SIZE; // todo
    int clickedRow = (y -BOARD_Y)/CELL_SIZE; // todo
    game.move(clickedRow, clickedCol);
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;

    }
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    Tictactoe game;
    game.init();
    graphics.render(game);


    SDL_Event event;
    int x, y;

    bool quit = false;

    while (!quit) {

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 quit = true;
                 break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                processClick(x, y, game);
                graphics.render(game);

        }
        SDL_Delay(100);
    }

    graphics.quit();
    return 0;


}
