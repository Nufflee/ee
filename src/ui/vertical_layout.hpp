#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "ui_element.hpp"
#include "layout_type.hpp"

struct VerticalLayout : UiElement
{
  std::vector<UiElement *> elements;
  LayoutType type;

  VerticalLayout(const std::vector<UiElement *> elements, const Vec2i position, const Size2 size, const LayoutType type)
      : UiElement(position, size), elements(elements), type(type)
  {
    assert(type == LayoutType::Fixed && elements[1]->size.is_zero());
  }

  void render(SDL_Renderer *renderer) override;
};