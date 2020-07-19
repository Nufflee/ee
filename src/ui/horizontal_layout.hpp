#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "ui_element.hpp"
#include "layout_type.hpp"
#include "../vec2.hpp"

struct HorizontalLayout : UiElement
{
  std::vector<UiElement *> elements;
  LayoutType type;

  HorizontalLayout(const std::vector<UiElement *> elements, const Vec2i position, const Size2 size, const LayoutType type)
      : UiElement(position, size), elements(elements), type(type) {}

  void render(SDL_Renderer *renderer) override;
};
