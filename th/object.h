#ifndef __OBJECT_H
#define __OBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>
#include "defs.h"

struct round_bullet
{
    SDL_Texture* texture;
    SDL_Rect hitbox;
    SDL_Point velocity;

    double angle;

    round_bullet(int x , int y, double angle)
    {

        hitbox.h = 10;
        hitbox.w = 10;
        hitbox.x = x;
        hitbox.y = y;
        velocity.x = 2 * cos(angle);
        velocity.y = 2 * sin(angle);
    }

    void load_bullet(SDL_Renderer* renderer)
    {
    texture = IMG_LoadTexture(renderer , "red_bullet.png");
    if (texture == NULL) {
        SDL_Log("Failed to load bullet texture: %s", IMG_GetError());
        }
    SDL_RenderCopy(renderer , texture , NULL , &hitbox );
    }
      void move1()
    {
        angle += 1;
        hitbox.x = SCREEN_WIDTH / 2 + radius * cos(angle);
        hitbox.y = SCREEN_HEIGHT / 2 + radius * sin(angle);
    }
    void move()
    {
        hitbox.x += velocity.x;
        hitbox.y += velocity.y;
    }
    void move2(double spreadAngle)
    {

    double newVelocityX = velocity.x * cos(spreadAngle) - velocity.y * sin(spreadAngle);
    double newVelocityY = velocity.x * sin(spreadAngle) + velocity.y * cos(spreadAngle);


    hitbox.x += newVelocityX;
    hitbox.y += newVelocityY;
    }
    void move3(int numBullets)
{
    double spreadAngle = 2 * M_PI / numBullets;

    for (int i = 0; i < numBullets; i++)
    {

        double newVelocityX = velocity.x * cos(i * spreadAngle) - velocity.y * sin(i * spreadAngle);
        double newVelocityY = velocity.x * sin(i * spreadAngle) + velocity.y * cos(i * spreadAngle);


        round_bullet newBullet(hitbox.x, hitbox.y, 0);
        newBullet.velocity.x = newVelocityX;
        newBullet.velocity.y = newVelocityY;


    }
}
};

struct Player
{
    SDL_Texture* texture;
    SDL_Rect hitbox;
    Player()
    {
        hitbox.h = 40;
        hitbox.w = 20;
        hitbox.x = SCREEN_WIDTH/2 - hitbox.w/2;
        hitbox.y = SCREEN_HEIGHT - 100;
    }

    void load_player(SDL_Renderer* renderer)
    {
        texture = IMG_LoadTexture(renderer , "player.png");
        if (texture == NULL) {
        SDL_Log("Failed to load player texture: %s", IMG_GetError());
        }
    SDL_RenderCopy(renderer , texture , NULL , &hitbox );
    }

    void mouse_movement(SDL_Event event)
    {
        if(event.type == SDL_MOUSEMOTION)
        {
            hitbox.x = event.motion.x - hitbox.w / 2;
            hitbox.y = event.motion.y - hitbox.h / 2;
        }
        SDL_Delay(10);
    }

    bool check_collision(round_bullet bullet)
    {
        if (hitbox.x < bullet.hitbox.x + bullet.hitbox.w &&
            hitbox.x + hitbox.w > bullet.hitbox.x &&
            hitbox.y < bullet.hitbox.y + bullet.hitbox.h &&
            hitbox.y + hitbox.h > bullet.hitbox.y)
        {
            return true;
        }
        return false;
    }

};

#endif // __OBJECT_H
