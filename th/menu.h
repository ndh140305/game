#ifndef __MENU_H
#define __MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"

struct Button
{
    const char* text;
    SDL_Color black = {0, 0, 0, 255};
    TTF_Font* font = loadFont("fonts.ttf" , 40);
    SDL_Texture* texture;
    SDL_Rect hitbox;
    Button (int _x , int _y , int _w , int _h)
    {
        hitbox = {_x , _y , _w , _h};
    }
    void name (const char* _text , SDL_Renderer* renderer)
    {
        text = _text;
        texture = renderText (_text , font , black , renderer);
    }
    void render (SDL_Renderer* renderer)
    {
        renderTexture (renderer , texture , hitbox.x , hitbox.y );
    }
};

vector<Button> create_menu(SDL_Renderer* renderer)
{
    vector<Button> menu;
    menu.push_back (Button(720 , 100 , 100 , 30 ));
    menu.push_back (Button(740 , 150 , 100 , 30 ));
    menu.push_back (Button(750 , 200 , 100 , 30 ));
    menu.push_back (Button(770 , 50 , 100 , 100 ));
    menu[0].name("New Game" , renderer);
    menu[1].name("Pause" , renderer);
    menu[2].name("Exit" , renderer);
    menu[3].name((to_string(score)).c_str() , renderer );
    return menu;
}


void show_menu(vector<Button> &menu , SDL_Renderer* renderer)
{
    if (score != prevScore)
    {
            menu[3].name((to_string(score)).c_str() , renderer );
    }
    for (int i=0 ; i<4 ; ++i)
    {
        menu[i].render(renderer);
    }
}

void click_button (SDL_Event &event , vector<Button> &buttons)
{
    int a;
    int b;
    SDL_GetMouseState(&a, &b);
    SDL_PollEvent(&event);
    for (Button& i: buttons)
    {
        if (event.type == SDL_MOUSEBUTTONDOWN && (a > i.hitbox.x && a < i.hitbox.x + i.hitbox.w && b > i.hitbox.y && b < i.hitbox.y + i.hitbox.h)) {
                if (i.text == "Exit")
                {
                    END_GAME = true;
                    cout << "Exit clicked" << endl;
                }
                else if (i.text == "Pause")
                {
                    PAUSE = (PAUSE) ? false : true;
                    cout << "Pause clicked" << endl;
                }
                else if (i.text == "New Game")
                {
                    score = 0;
                }
        }
    }

}
#endif // __MENU_H


