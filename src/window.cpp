#include "window.hpp"

Window *Window::instance = nullptr;

Window::Window(const char *title, uint32_t width, uint32_t height)
    : m_title(title), m_width(width), m_height(height)
{
  instance = this;
}

Window::~Window()
{
  SDL_DestroyWindow(m_window);
}

bool Window::create()
{
  m_window = SDL_CreateWindow(
      m_title,
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      m_width, m_height, SDL_WINDOW_SHOWN);

  return m_window != nullptr;
}

void Window::on_event(const SDL_Event event)
{
  if (event.type == SDL_WINDOWEVENT)
  {
    if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
    {
      m_width = event.window.data1;
      m_height = event.window.data2;
    }
  }
}

Window *Window::the()
{
  assert(instance);

  return instance;
}