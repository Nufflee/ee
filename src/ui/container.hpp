#pragma once

#include <SDL2/SDL.h>

#include "ui_element.hpp"

struct Container : UiElement
{
  SDL_Color color;

  Container(Vec2i position, Size2 size, SDL_Color color) : UiElement(position, size), color(color) {}

  void render(SDL_Renderer *) override;
};