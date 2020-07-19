#include "horizontal_layout.hpp"
#include "color_resetter.hpp"

void HorizontalLayout::render(SDL_Renderer *renderer)
{
  ColorResetter resetter(renderer);

  int window_width, window_height;
  SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

  if (type == LayoutType::Centered)
  {
    for (size_t i = 0; i < elements.size(); i++)
    {
      auto element = elements[i];

      element->size = {size.width / elements.size(), size.height};

      element->position = {(int)(position.x + element->size.width.to_pixels(window_width) * i), position.y};
    }
  }
  else
  {
    assert(elements.size() <= 2 && "Not supported yet because idk how to implement Pepega");

    elements[1]->position = {position.x + elements[0]->size.width.to_pixels(window_width), position.y};
    elements[1]->size = {Value::pixels(size.width.to_pixels(window_width) - elements[0]->size.width.to_pixels(window_width)), size.height};
  }

  for (auto element : elements)
  {
    element->render(renderer);
  }
}