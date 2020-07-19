#pragma once

#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ui_element.hpp"
#include "vec2.hpp"
#include "size2.hpp"

struct TextArea : UiElement
{
  TTF_Font *font;
  SDL_Color color;

  TextArea(const Vec2i position, const Size2 size, const std::string &content, TTF_Font *font, const SDL_Color color);

  void render(SDL_Renderer *renderer) override;

  void on_event(const SDL_Event event);

private:
  Vec2<size_t> m_cursor_position;
  std::vector<std::string> m_lines;

  int m_font_height;
  int m_font_advance;
  int m_wrap_width;

  void render_line(SDL_Renderer *renderer, const std::string &line, const int line_number);

  void set_content(const std::string &content, const int wrap_width);
};
