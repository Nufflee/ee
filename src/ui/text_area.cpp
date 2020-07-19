#include "text_area.hpp"

#include "window.hpp"

template <typename L, typename R>
constexpr const std::common_type_t<L, R> min(const L left, const R right)
{
  if (left < right)
  {
    return left;
  }

  return right;
}

TextArea::TextArea(const Vec2i position, const Size2 size, const std::string &content, Container &line_number_container, TTF_Font *font, const SDL_Color color)
    : UiElement(position, size), font(font), color(color), m_line_number_container(line_number_container)
{
  m_font_height = TTF_FontHeight(font);
  TTF_GlyphMetrics(font, 0, nullptr, nullptr, nullptr, nullptr, &m_font_advance);

  set_content(content, size.width.to_pixels(Window::the()->get_width()));
}

void TextArea::render(SDL_Renderer *renderer)
{
  int window_width, window_height;
  SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

  m_wrap_width = size.width.to_pixels(window_width);

  size_t line_number = 0;

  for (; line_number < m_lines.size(); line_number++)
  {
    render_line(renderer, m_lines[line_number], line_number + 1);
  }

  SDL_Rect cursor_rect = {
      position.x + (int)(m_cursor_position.x * m_font_advance),
      position.y + (int)(m_cursor_position.y * m_font_height),
      3,
      m_font_height,
  };
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &cursor_rect);
}

void TextArea::on_event(SDL_Event event)
{
  auto insert_line = [=](size_t line) {
    if (line >= m_lines.size())
    {
      m_lines.insert(m_lines.begin() + line, "");
    }
  };

  if (event.type == SDL_TEXTINPUT)
  {
    m_lines[m_cursor_position.y].insert(m_cursor_position.x, event.edit.text);

    if (m_cursor_position.x * m_font_advance >= (size_t)m_wrap_width)
    {
      m_cursor_position.y++;
      m_cursor_position.x = 0;

      insert_line(m_cursor_position.y);
    }
    else
    {
      m_cursor_position.x++;
    }
  }
  else if (event.type == SDL_KEYDOWN)
  {
    int key = event.key.keysym.sym;

    if (key == SDLK_BACKSPACE)
    {
      if (m_cursor_position.is_zero())
      {
        return;
      }

      if (m_cursor_position.x == 0 && m_cursor_position.y > 0)
      {
        if (m_lines[m_cursor_position.y].size() == 0)
        {
          m_lines.erase(m_lines.begin() + m_cursor_position.y);
        }

        m_cursor_position.y--;
        m_cursor_position.x = m_lines[m_cursor_position.y].size();
      }
      else
      {
        m_lines[m_cursor_position.y].pop_back();

        if (m_cursor_position.x > 0)
        {
          m_cursor_position.x--;
        }
      }
    }
    else if (key == SDLK_RETURN)
    {
      m_cursor_position.x = 0;
      m_cursor_position.y++;

      insert_line(m_cursor_position.y);
    }
    else if (key == SDLK_LEFT)
    {
      if (m_cursor_position.x == 0)
      {
        if (m_cursor_position.y > 0)
        {
          m_cursor_position.y--;
          m_cursor_position.x = m_lines[m_cursor_position.y].size();
        }
      }
      else
      {
        m_cursor_position.x--;
      }
    }
    else if (key == SDLK_RIGHT)
    {
      if (m_cursor_position.x == m_lines[m_cursor_position.y].size())
      {
        if (m_cursor_position.y < m_lines.size() - 1)
        {
          m_cursor_position.x = 0;
          m_cursor_position.y++;
        }
      }
      else
      {
        m_cursor_position.x++;
      }
    }
    else if (key == SDLK_UP)
    {
      if (m_cursor_position.y > 0)
      {
        m_cursor_position.y--;
        m_cursor_position.x = min(m_cursor_position.x, m_lines[m_cursor_position.y].size());
      }
      else
      {
        m_cursor_position.x = 0;
      }
    }
    else if (key == SDLK_DOWN)
    {
      if (m_cursor_position.y < m_lines.size() - 1)
      {
        m_cursor_position.y++;
        m_cursor_position.x = min(m_cursor_position.x, m_lines[m_cursor_position.y].size());
      }
      else
      {
        m_cursor_position.x = m_lines[m_cursor_position.y].size();
      }
    }
    else if (key == SDLK_HOME)
    {
      m_cursor_position.x = 0;
    }
    else if (key == SDLK_END)
    {
      m_cursor_position.x = m_lines[m_cursor_position.y].size();
    }
  }
}

void TextArea::render_line(SDL_Renderer *renderer, const std::string &line, const int line_number)
{
  int text_width, text_height;
  TTF_SizeText(font, line.c_str(), &text_width, &text_height);

  SDL_Surface *font_surface = TTF_RenderText_Blended(font, line.c_str(), color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, font_surface);

  SDL_Rect rect = {position.x, position.y + (line_number - 1) * text_height, text_width, text_height};
  SDL_RenderCopy(renderer, texture, NULL, &rect);

  render_line_number(renderer, line_number);
}

void TextArea::render_line_number(SDL_Renderer *renderer, const int line_number)
{
  std::string line_number_str = std::to_string(line_number);

  int text_width, text_height;
  TTF_SizeText(font, line_number_str.c_str(), &text_width, &text_height);

  int container_width = m_line_number_container.size.width.to_pixels(Window::the()->get_width());

  constexpr int expansion = 30;

  if (container_width - expansion < text_width)
  {
    m_line_number_container.size.width = Value::pixels(text_width + expansion);
  }

  SDL_Surface *font_surface = TTF_RenderText_Blended(font, line_number_str.c_str(), {180, 180, 180, 255});
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, font_surface);

  SDL_Rect rect = {m_line_number_container.position.x + (container_width - text_width - 10), position.y + (line_number - 1) * text_height, text_width, text_height};
  SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void TextArea::set_content(const std::string &content, const int wrap_width)
{
  m_lines.clear();

  if (content.size() == 0)
  {
    m_lines.push_back({});

    return;
  }

  int last = 0;

  for (size_t i = 0; i < content.size(); i++)
  {
    char c = content[i];

    if (c == '\n' || (i - last) * m_font_advance > (size_t)wrap_width)
    {
      m_lines.push_back(content.substr(last, i - last));

      if ((i - last) * m_font_advance > (size_t)wrap_width)
      {
        last = i;
      }
      else
      {
        last = i + 1;
      }
    }
  }

  m_lines.push_back(content.substr(last, content.size() - last));
}