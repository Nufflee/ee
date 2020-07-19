#include "value.hpp"

int Value::to_pixels(const int reference) const
{
  if (m_type == Type::Percentage)
  {
    return roundf(reference * m_value);
  }
  else
  {
    return m_value;
  }
}

Value Value::operator*(const int a) const
{
  float result = m_value * a;

  if (m_type == Type::Pixel)
  {
    result = roundf(result);
  }

  return {result, m_type};
}

Value Value::operator/(const int a) const
{
  float result = m_value / a;

  if (m_type == Type::Pixel)
  {
    result = roundf(result);
  }

  return {result, m_type};
}