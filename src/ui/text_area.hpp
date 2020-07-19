#pragma once

#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ui_element.hpp"
#include "container.hpp"
#include "vec2.hpp"
#include "size2.hpp"

struct TextArea : UiElement
{
  TTF_Font *font;
  SDL_Color color;

  TextArea(const Vec2i position, const Size2 size, const std::string &content, Container &line_number_container, TTF_Font *font, const SDL_Color color);

  void render(SDL_Renderer *renderer) override;

  void on_event(const SDL_Event event);

private:
  Vec2<size_t> m_cursor_position;
  std::vector<std::string> m_lines;

  Container &m_line_number_container;

  int m_font_height;
  int m_font_advance;
  int m_wrap_width;

  void render_line(SDL_Renderer *, const std::string &line, const int line_number);
  void render_line_number(SDL_Renderer *, const int line_number);

  void set_content(const std::string &content, const int wrap_width);
};
