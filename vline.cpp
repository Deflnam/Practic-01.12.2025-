#include "vline.hpp"

namespace top 
{

  VLine::VLine(int x, int y, int len) : IDraw(), start{x,y}, length(len)
  {
    if (len == 0) 
    {
      throw std::logic_error("USER invalid");
    }
  }

  p_t VLine::begin() const
  {
    return start;
  }

  p_t VLine::next(p_t p) const
  {
    if (p.y == start.y + length - 1) 
    {
      return start;
    }
    if (length > 0) 
    {
      return p_t{start.x, p.y + 1};
    }
    return p_t{start.x, p.y - 1};
  }
}
