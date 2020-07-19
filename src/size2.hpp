#pragma once

#include "value.hpp"

struct Size2
{
  Value width, height;

  Size2() : width(0_pixels), height(0_pixels) {}

  Size2(Value width, Value height) : width(width), height(height)
  {
    assert(width.raw_value() >= 0 && height.raw_value() >= 0);
  }

  inline bool is_zero() const { return width.is_zero() && height.is_zero(); }
};
