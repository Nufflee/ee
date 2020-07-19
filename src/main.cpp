#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "window.hpp"
#include "ui/container.hpp"
#include "ui/vertical_layout.hpp"
#include "ui/text_area.hpp"
#include "vec2.hpp"
#include "size2.hpp"
#include "value.hpp"

int main()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    abort();
  }

  Window window("editor", 1921, 1081);

  if (!window.create())
  {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    abort();
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window.raw_sdl(), -1, SDL_RENDERER_ACCELERATED);

  if (!renderer)
  {
    fprintf(stderr, "could not create renderer: %s\n", SDL_GetError());
    abort();
  }

  if (TTF_Init() < 0)
  {
    fprintf(stderr, "could not initialize sdl2 ttf: %s\n", TTF_GetError());
    abort();
  }

  TTF_Font *font = TTF_OpenFont("resources/FiraCode-Regular.ttf", 25);

  if (!font)
  {
    fprintf(stderr, "could not load font: %s\n", TTF_GetError());
    abort();
  }

  bool should_quit = false;

  /*
  Container c1 = {{}, {}, {30, 30, 30, 255}};
  Container c2 = {{}, {}, {20, 20, 20, 255}};
  Container c3 = {{}, {}, {10, 10, 10, 255}};
  Container c4 = {{}, {}, {40, 40, 40, 255}};

  HorizontalLayout horizontal_layout1 = {{&c1, &c2}, {0, 0}, {100_percent, 100_percent}, LayoutType::Centered};
  HorizontalLayout horizontal_layout2 = {{&c3, &c4}, {0, 0}, {100_percent, 100_percent}, LayoutType::Centered};
  VerticalLayout layout = {{&horizontal_layout1, &horizontal_layout2}, {0, 0}, {100_percent, 100_percent}, LayoutType::Centered};
  */

  const int top_bar_height = 50;

  Container top_bar = {{}, {100_percent, Value::pixels(top_bar_height)}, {30, 30, 30, 255}};
  Container content = {{0, top_bar_height}, {}, {40, 40, 40, 255}};
  VerticalLayout layout = {{&top_bar, &content}, {}, {100_percent, 100_percent}, LayoutType::Fixed};

  const char *code = "this is a very long test string to check if our content setting and line wrapping works properly. i really do hope that it does but i dont know.";
  //const char *code = "";

  TextArea text_area = {{10, top_bar_height + 10}, {25_percent, 100_percent}, code, font, {255, 255, 255, 255}};

  while (!should_quit)
  {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        should_quit = true;
        break;
      }

      text_area.on_event(event);
      Window::the()->on_event(event);
    }

    SDL_SetRenderDrawColor(renderer, 255, 127, 127, 255);
    SDL_RenderClear(renderer);

    layout.render(renderer);
    text_area.render(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(1000 / 30);
  }

  SDL_DestroyRenderer(renderer);
  TTF_CloseFont(font);

  SDL_Quit();
  TTF_Quit();

  return 0;
}