#include "dline.hpp"
#include <stdexcept>

top::DLine::DLine(int x, int y, int len) : 
  IDraw(), 
  start{x, y}, 
  length(len)
{
  if (len <= 0)
  {
    throw std::logic_error("user invalid");
  }
}

top::p_t top::DLine::begin() const
{
  return start;
}

top::p_t top::DLine::next(p_t p) const
{
  if (p.x - start.x == p.y - start.y)
  {
    if (p.x == start.x + length - 1 && p.y == start.y + length - 1)
    {
      return start;
    }
    return {p.x + 1, p.y + 1};
  }
  return start;
}
