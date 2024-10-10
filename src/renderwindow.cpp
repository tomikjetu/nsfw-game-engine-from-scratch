#include <../../SDL2/include/SDL2/SDL.h>
#include <../../SDL2/include/SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
    : window(NULL), renderer(NULL)
{
  window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
  if (window == NULL)
    std::cout << "Window initialization error: " << SDL_GetError() << std::endl;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(renderer, 0xf9, 0x82, 0x9b, 255);
}

SDL_Texture *RenderWindow::loadTexture(const char *p_filePath)
{
  SDL_Texture *texture = NULL;
  texture = IMG_LoadTexture(renderer, p_filePath);
  if (texture == NULL)
    std::cout << "Failed to load a texture: " << SDL_GetError() << std::endl;
  return texture;
}

void RenderWindow::render(Entity &p_entity)
{
  SDL_Rect src; //display sprite, crop it from X and Y - W and H pixels
  src.x = p_entity.getCurrentFrame().x;
  src.y = p_entity.getCurrentFrame().y;
  src.w = p_entity.getCurrentFrame().w;
  src.h = p_entity.getCurrentFrame().h;

  SDL_Rect dst; //display at coords - X,Y, scale - W, H
  dst.x = p_entity.pos.x * p_entity.getScaler().x;
  dst.y = p_entity.pos.y * p_entity.getScaler().y;
  dst.w = p_entity.getCurrentFrame().w * p_entity.getScaler().x;
  dst.h = p_entity.getCurrentFrame().h * p_entity.getScaler().y;

  SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::display()
{
  SDL_RenderPresent(renderer);
}

void RenderWindow::clear()
{
  SDL_RenderClear(renderer);
}

void RenderWindow::cleanUp()
{
  SDL_DestroyWindow(window);
}