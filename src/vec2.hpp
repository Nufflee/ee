#pragma once

template <typename T>
struct Vec2
{
  T x, y;

  Vec2() : x(0), y(0) {}
  Vec2(const T x, const T y) : x(x), y(y) {}

  inline bool is_zero() const { return x == 0 && y == 0; }

  inline bool operator>=(T other) const { return x >= other && y >= other; }
};

using Vec2i = Vec2<int>;