#pragma once
#include <../../SDL2/include/SDL2/SDL.h>
#include <../../SDL2/include/SDL2/SDL_image.h>

#include "Vector2d.hpp"

class Scaler
{
public:
    Scaler(float p_x, float p_y);
    float x, y;
};

class Entity
{
public:
    Entity(SDL_Texture *p_tex, Vector2d p_pos, Scaler p_scaler = Scaler(1, 1));
    Vector2d pos;
    SDL_Texture *getTex();
    void setTex(SDL_Texture *p_tex);
    SDL_Rect getCurrentFrame();
    Scaler getScaler();
    void setScaler(Scaler p_scaler);

private:
    SDL_Rect currentFrame;
    SDL_Texture *tex;
    Scaler scaler;
};