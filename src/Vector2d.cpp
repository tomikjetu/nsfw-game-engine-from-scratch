#include <../../SDL2/include/SDL2/SDL.h>
#include <../../SDL2/include/SDL2/SDL_image.h>
#include <iostream>

#include "Vector2d.hpp"

void Vector2d::add(Vector2d vector)
{
  x += vector.x;
  y += vector.y;
}
void Vector2d::set(Vector2d vector)
{
  x = vector.x;
  y = vector.y;
}