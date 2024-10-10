#pragma once
#include <../../SDL2/include/SDL2/SDL.h>
#include <../../SDL2/include/SDL2/SDL_image.h>

struct Vector2d
{

  Vector2d() : x(0.0f), y(0.0f) {}
  Vector2d(float p_x, float p_y) : x(p_x), y(p_y) {}
  float x, y;

  void add(Vector2d vector);
  void set(Vector2d vector);
};