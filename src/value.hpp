#pragma once

#include <math.h>
#include <assert.h>

struct Value
{
  enum class Type
  {
    Percentage,
    Pixel
  };

  Value(const float value, const Type type) : m_value(value), m_type(type) {}

  static Value pixels(const int value)
  {
    return {(float)value, Type::Pixel};
  }

  static Value percentage(const int value)
  {
    return {(float)value / 100, Value::Type::Percentage};
  }

  int to_pixels(const int reference) const;

  inline float raw_value() const { return m_value; }
  inline bool is_zero() const { return m_value == 0; }

  Value operator*(const int other) const;
  Value operator/(const int other) const;

private:
  float m_value;
  Type m_type;
};

static inline Value operator""_pixels(const unsigned long long value)
{
  return Value::pixels(value);
}

static inline Value operator""_percent(const unsigned long long value)
{
  return Value::percentage(value);
}