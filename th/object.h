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

    bool isActive = true;
    int frame = 0;
    SDL_Texture* texture;
    SDL_FRect hitbox;
    SDL_FPoint speed;
    int radius;

    round_bullet (int XOffset , int YOffset , float speed1 , double angle)
    {
        radius = 5;
        hitbox = {XOffset , YOffset , 15 , 15};
        speed.x = 1.0 * speed1 * cosf(angle * M_PI / 180.0);
        speed.y = 1.0 * speed1 * sinf(angle * M_PI / 180.0);
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
    SDL_RenderCopyF(renderer , texture , NULL , &hitbox );
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
    bool isMoving = false;
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
    void load_texture (SDL_Renderer* renderer)
    {
        texture = IMG_LoadTexture(renderer , "img//player1.png");
        if (texture == NULL)
        {
            SDL_Log("Failed to load player texture: %s", IMG_GetError());
        }
    }
    void render(SDL_Renderer* renderer)
    {
        if (isMoving == true)
        {
            SDL_RenderCopy(renderer , texture , NULL , &hitbox );
            isMoving = false;
        }
    }

    void keyboard_movement()
    {
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_UP] && hitbox.y >= 5)
            hitbox.y -= PLAYER_SPEED;
            isMoving = true;
        if (keystate[SDL_SCANCODE_DOWN] && hitbox.y <= SCREEN_HEIGHT - hitbox.h - 5)
            hitbox.y += PLAYER_SPEED;
            isMoving = true;
        if (keystate[SDL_SCANCODE_LEFT] && hitbox.x >= 5)
            hitbox.x -= PLAYER_SPEED;
            isMoving = true;
        if (keystate[SDL_SCANCODE_RIGHT] && hitbox.x <= SCREEN_WIDTH - hitbox.w - 5)
            hitbox.x += PLAYER_SPEED;
            isMoving = true;
    }

     void shoot_bullets(SDL_Renderer* renderer)
    {
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
        Uint32 currentTime = SDL_GetTicks();

        if (keystate[SDL_SCANCODE_X] && (currentTime - lastShotTime) >= shotCooldown)
        {
            round_bullet* bullet = new round_bullet(hitbox.x + hitbox.w / 2, hitbox.y, PLAYER_BULLET_SPEED , 270);
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
                SDL_RenderCopyF(renderer, (*it)->texture, NULL, &(*it)->hitbox);
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
    int frame = 0;
    int health = 100;
    SDL_Texture* texture;
    SDL_Rect hitbox;
    Enemy(int x , int y)
    {
        hitbox = {x , y , 50 , 50};
    }
    void load_texture (SDL_Renderer* renderer)
    {
        texture = IMG_LoadTexture (renderer , "img//enemy1.png");
    }
    void render(SDL_Renderer* renderer)
    {
        SDL_RenderCopy(renderer , texture , NULL , &hitbox);
    }

    void movement (int direction)
    {
        if (frame > 10){
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
            if (hitbox.y <SCREEN_HEIGHT/5*3)
                hitbox.y += ENEMY_SPEED;

            break;
        }
        frame = 0;
        }
        frame++;
    }
};

vector<round_bullet> createSpreadBullets(int xOffset, int yOffset, SDL_Renderer* renderer) {
    vector<round_bullet> bullets;
    for (int i = 0; i <= 35; i++)
    {
        bullets.push_back(round_bullet(xOffset, yOffset ,ENEMY_BULLET_SPEED , 0 + 10*i));
        bullets.push_back(round_bullet(xOffset, yOffset ,ENEMY_BULLET_SPEED + 1 , 0 + 10*i));
        bullets.push_back(round_bullet(xOffset, yOffset ,ENEMY_BULLET_SPEED + 2 , 0 + 10*i));
    }
    return bullets;
}

vector<round_bullet> createFastBullets(float xOffset, float yOffset, SDL_Renderer* renderer , float targetX , float targetY)
{
    vector<round_bullet> bullets;
    float angle = 1.0 * atan((targetY - yOffset) / (targetX - xOffset)) + 90;
    for (int i=1 ; i<=10 ; ++i)
    {
        bullets.push_back(round_bullet(xOffset , yOffset , 1.0*i , angle));
    }
    return bullets;
}

void reloadBullets (int xOffset , int yOffset , vector<round_bullet>& bullets)
{
    for (round_bullet& i: bullets)
    {
        i.hitbox.x = xOffset;
        i.hitbox.y = yOffset;
    }
}
void shootBullets(vector<round_bullet>& bullets, Player& player, SDL_Renderer* renderer) {
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        if (!it->isOutOfScreen())
        {
            it->shoot();
            it->draw_bullet(renderer);
        }
        if (player.check_collision(*it))
        {
            END_GAME = true;
            break;
        }
        /*
        else {
            ++it;
        }*/
        ++it;
    }
}

#endif // __OBJECT_H
