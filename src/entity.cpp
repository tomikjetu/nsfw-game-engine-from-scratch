#include <../../SDL2/include/SDL2/SDL.h>
#include <../../SDL2/include/SDL2/SDL_image.h>
#include <iostream>

#include "Entity.hpp"

Scaler::Scaler(float p_x, float p_y) : x(p_x), y(p_y) {}

Entity::Entity(SDL_Texture *p_tex, Vector2d p_pos, Scaler p_scaler)
    : pos(p_pos), tex(p_tex), scaler(p_scaler)
{
    SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h); //get the image resolution
    currentFrame.x = 0;
    currentFrame.y = 0;
}

void Entity::setTex(SDL_Texture *p_tex)
{
    SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h); //get the image resolution
    currentFrame.x = 0;
    currentFrame.y = 0;
    tex = p_tex;
}

SDL_Texture *Entity::getTex()
{
    return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
    return currentFrame;
}

Scaler Entity::getScaler()
{
    return scaler;
}

void Entity::setScaler(Scaler p_scaler)
{
    scaler = p_scaler;
}