#pragma once

#include <SDL2/SDL.h>

#include "size2.hpp"

struct Window
{
  Window(const char *title, uint32_t width, uint32_t height);
  ~Window();

  static Window *the();

  bool create();
  void on_event(const SDL_Event);

  inline SDL_Window *raw_sdl() { return m_window; }
  inline int get_width() { return m_width; }
  inline int get_height() { return m_height; }

private:
  static Window *instance;

  SDL_Window *m_window;
  const char *m_title;
  uint32_t m_width, m_height;
};