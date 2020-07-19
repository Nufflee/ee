#pragma once

#include "vec2.hpp"
#include "size2.hpp"

struct UiElement
{
  Vec2i position;
  Size2 size;

  UiElement(const Vec2i position, const Size2 size) : position(position), size(size)
  {
    assert(position >= 0);
  }

  virtual void render(SDL_Renderer *) {}
};