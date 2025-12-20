#include "rectangle.hpp"
#include <stdexcept>

top::Rectangle::Rectangle(int x, int y, int a, int b) : 
  IDraw(), 
  start{x, y}, 
  a_(a), 
  b_(b)
{
  if (a <= 0 || b <= 0)
  {
    throw std::logic_error("user invalid");
  }
}

top::p_t top::Rectangle::begin() const
{
  return start;
}

top::p_t top::Rectangle::next(p_t p) const
{
  if (p.x == start.x && p.y < start.y + b_ - 1)
  {
    return {p.x, p.y + 1};
  }
  else if (p.y == start.y + b_ - 1 && p.x < start.x + a_ - 1)
  {
    return {p.x + 1, p.y};
  }
  else if (p.x == start.x + a_ - 1 && p.y > start.y)
  {
    return {p.x, p.y - 1};
  }
  else if (p.y == start.y && p.x > start.x)
  {
    return {p.x - 1, p.y};
  }
  return start;
}
