#include "container.hpp"
#include "color_resetter.hpp"

void Container::render(SDL_Renderer *renderer)
{
  assert(!size.is_zero());

  ColorResetter resetter(renderer);

  int window_width, window_height;
  SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

  SDL_Rect rect = {position.x, position.y, size.width.to_pixels(window_width), size.height.to_pixels(window_height)};

#if 0
    printf("Container:\n");
    printf("\tPos:  (%d, %d)\n", rect.x, rect.y);
    printf("\tSize: (%d, %d)\n", rect.w, rect.h);
#endif

  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &rect);
}