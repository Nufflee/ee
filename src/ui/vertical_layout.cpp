#include "vertical_layout.hpp"
#include "color_resetter.hpp"

void VerticalLayout::render(SDL_Renderer *renderer)
{
  ColorResetter resetter(renderer);

  int window_width, window_height;
  SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

  if (type == LayoutType::Centered)
  {
    for (size_t i = 0; i < elements.size(); i++)
    {
      auto element = elements[i];

      element->size = {size.width, size.height / elements.size()};

      element->position = {position.x, (int)(position.y + element->size.height.to_pixels(window_height) * i)};
    }
  }
  else
  {
    assert(elements.size() <= 2 && "Not supported yet because idk how to implement Pepega");

    elements[1]->size = {size.width, Value::pixels(size.height.to_pixels(window_height) - elements[0]->size.height.to_pixels(window_height))};
  }

  for (auto element : elements)
  {
    element->render(renderer);
  }
}