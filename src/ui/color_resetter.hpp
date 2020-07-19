#pragma once

#include <SDL2/SDL.h>

struct ColorResetter
{
  ColorResetter(SDL_Renderer *renderer)
      : m_renderer(renderer)
  {
    SDL_GetRenderDrawColor(renderer, &m_old_color.r, &m_old_color.g, &m_old_color.b, &m_old_color.a);
  }

  ~ColorResetter()
  {
    SDL_SetRenderDrawColor(m_renderer, m_old_color.r, m_old_color.g, m_old_color.b, m_old_color.a);
  }

private:
  SDL_Renderer *m_renderer;
  SDL_Color m_old_color;
};