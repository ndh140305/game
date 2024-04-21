#ifndef __OBJECT_H
#define __OBJECT_H

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>
#include "defs.h"

using namespace std;

struct round_bullet
{
    SDL_Texture* texture;
    SDL_Rect hitbox;
    SDL_Point speed;
    int radius;

    round_bullet (int point_x , int point_y , int speed_x, int speed_y )
    {
        radius = 5;
        hitbox.x = point_x;
        hitbox.y = point_y;
        hitbox.w = 10;
        hitbox.h = 10;
        speed.x = speed_x;
        speed.y = speed_y;
    }

    round_bullet (int point_x , int point_y , double angle)
    {
        radius = 5;
        hitbox.x = point_x;
        hitbox.y = point_y;
        hitbox.w = 15;
        hitbox.h = 15;
        speed.x = INTIAL_SPEED * cos(angle * M_PI / 180.0);
        speed.y = INTIAL_SPEED * sin(angle * M_PI / 180.0);
    }

    void draw_bullet(SDL_Renderer* renderer)
    {
        SDL_SetRenderDrawColor(renderer, 255 , 255 , 255 ,255);
        for(int w = 0; w < radius * 2; w++)
        {
            for(int h = 0; h < radius * 2; h++)
            {
                int dx = radius - w;
                int dy = radius - h;
                if ((dx*dx + dy*dy) <= (radius * radius))
                {
                    SDL_RenderDrawPoint(renderer, hitbox.x + dx, hitbox.y + dy);
                }
            }
        }
    }

    void load_bullet(SDL_Renderer* renderer , int type)
    {
        switch (type){
            case 0:
                texture = IMG_LoadTexture(renderer , "img//red_bullet.png");
                break;
            case 1:
                texture = IMG_LoadTexture(renderer , "img//green_bullet.png");
                break;
        }

    if (texture == NULL) {
        SDL_Log("Failed to load bullet texture: %s", IMG_GetError());
        }
    SDL_RenderCopy(renderer , texture , NULL , &hitbox );
    }

    void shoot()
    {
        hitbox.x += speed.x;
        hitbox.y += speed.y;
    }

    bool isOutOfScreen()
    {
        return hitbox.x < 0 || hitbox.y < 0 || hitbox.x > SCREEN_WIDTH || hitbox.y > SCREEN_HEIGHT;
    }


};

struct Player
{
    SDL_Texture* texture;
    SDL_Rect hitbox;
    vector <round_bullet*> bullets;
    Uint32 lastShotTime;
    Uint32 shotCooldown;
    Player() : lastShotTime(0), shotCooldown(500)
    {
        hitbox.h = 50;
        hitbox.w = 50;
        hitbox.x = SCREEN_WIDTH/2 - hitbox.w/2;
        hitbox.y = SCREEN_HEIGHT - 100;
    }

    void render(SDL_Renderer* renderer)
    {
        texture = IMG_LoadTexture(renderer , "img//player1.png");
        if (texture == NULL) {
        SDL_Log("Failed to load player texture: %s", IMG_GetError());
        }
    SDL_RenderCopy(renderer , texture , NULL , &hitbox );
    }

    void keyboard_movement()
    {
         const Uint8 *keystate = SDL_GetKeyboardState(NULL);
         if (keystate[SDL_SCANCODE_UP] && hitbox.y >= 5)
            hitbox.y -= PLAYER_SPEED;
         if (keystate[SDL_SCANCODE_DOWN] && hitbox.y <= SCREEN_HEIGHT - hitbox.h - 5)
            hitbox.y += PLAYER_SPEED;
         if (keystate[SDL_SCANCODE_LEFT] && hitbox.x >= 5)
            hitbox.x -= PLAYER_SPEED;
         if (keystate[SDL_SCANCODE_RIGHT] && hitbox.x <= SCREEN_WIDTH - hitbox.w - 5)
            hitbox.x += PLAYER_SPEED;
    }

     void shoot_bullets(SDL_Renderer* renderer)
    {
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
        Uint32 currentTime = SDL_GetTicks();

        if (keystate[SDL_SCANCODE_X] && (currentTime - lastShotTime) >= shotCooldown)
        {
            round_bullet* bullet = new round_bullet(hitbox.x + hitbox.w / 2, hitbox.y, 0, -5);
            bullet->load_bullet(renderer, 0);
            bullets.push_back(bullet);
            lastShotTime = currentTime;
        }


        for (auto it = bullets.begin(); it != bullets.end(); )
        {
            (*it)->shoot();
            if ((*it)->isOutOfScreen())
            {
                delete *it;
                it = bullets.erase(it);
            }
            else
            {
                SDL_RenderCopy(renderer, (*it)->texture, NULL, &(*it)->hitbox);
                ++it;
            }
        }
    }

    void load(SDL_Renderer* renderer)
    {
        render(renderer);
        keyboard_movement();
        shoot_bullets(renderer);
    }

    bool check_collision(round_bullet& bullet)
    {
        if (COLLISION_ON && hitbox.x < bullet.hitbox.x + bullet.hitbox.w &&
            hitbox.x + hitbox.w > bullet.hitbox.x &&
            hitbox.y < bullet.hitbox.y + bullet.hitbox.h &&
            hitbox.y + hitbox.h > bullet.hitbox.y)
        {
            return true;
        }
        return false;
    }

};

struct Enemy
{
    SDL_Texture* texture;
    SDL_Rect hitbox;
    Enemy(int x , int y)
    {
        hitbox.x = x;
        hitbox.y = y;
        hitbox.w = 50;
        hitbox.h = 50;
    }
    void load_enemy(SDL_Renderer* renderer)
    {
        texture = IMG_LoadTexture (renderer , "img//enemy1.png");
        SDL_RenderCopy(renderer , texture , NULL , &hitbox);
    }

    void movement (int direction)
    {
        switch (direction)
        {
        case 0:
            if (hitbox.x > SCREEN_WIDTH/6)
                hitbox.x -= ENEMY_SPEED;

            break;
        case 1:
            if (hitbox.x < SCREEN_WIDTH*5/6)
                hitbox.x += ENEMY_SPEED;

            break;
        case 2:
            if (hitbox.y > SCREEN_HEIGHT/6)
                hitbox.y -= ENEMY_SPEED;

            break;
        case 3:
            if (hitbox.y <SCREEN_HEIGHT/2)
                hitbox.y += ENEMY_SPEED;

            break;
        }
    }

};
void normal_shot (int x , int y);

vector<round_bullet> createBullets(int numBullets, int xOffset, int yOffset, double angle, SDL_Renderer* renderer) {
    vector<round_bullet> bullets;
    for (int i = 0; i < numBullets; ++i) {
        bullets.push_back(round_bullet(xOffset + i * 20, yOffset + i * 20 , angle * i));
        bullets.back().load_bullet(renderer , rand()%2);
    }
    return bullets;
}

vector<round_bullet> createSpreadBullets(int numBullets, int xOffset, int yOffset, SDL_Renderer* renderer) {
    vector<round_bullet> bullets;
    int x = 2;
    for (int i = 0; i < numBullets; i++) {
        bullets.push_back(round_bullet(xOffset, yOffset , x , x*x+1));
        bullets.back().load_bullet(renderer , rand()%2);
    }
    return bullets;
}


void shootBullets(vector<round_bullet*>& bullets, Player& player, SDL_Renderer* renderer) {
    for (auto it = bullets.begin(); it != bullets.end(); )
        {
            (*it)->shoot();
            if ((player.check_collision(**it)))
            {
                END_GAME = true;
            }

            if ((*it)->isOutOfScreen())
            {
                delete *it;
                it = bullets.erase(it);
            }
            else
            {
                SDL_RenderCopy(renderer, (*it)->texture, NULL, &(*it)->hitbox);
                ++it;
            }
        }
}






#endif // __OBJECT_H
