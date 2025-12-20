#include "geom.hpp"
#include <stdexcept>
#include <algorithm>
bool top::operator==(p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y;
}
bool top::operator!=(p_t a, p_t b)
{
  return !(a == b);
}
size_t top::rows(Frame_t fr)
{
  return (fr.rightTop.y - fr.leftBott.y + 1);
}
size_t top::cols(Frame_t fr)
{
  return (fr.rightTop.x - fr.leftBott.x + 1);
}
top::Frame_t top::buildFrame(const p_t* ps, size_t s)
{
  if (!s)
  {
    throw std::logic_error("");
  }
  int minx = ps[0].x, maxx = ps[0].x;
  int miny = ps[0].y, maxy = ps[0].y;
  for (size_t i = 1; i < s; ++i) 
  {
    minx = std::min(minx, ps[i].x);
    maxx = std::max(maxx, ps[i].x);
    miny = std::min(miny, ps[i].y);
    maxy = std::max(maxy, ps[i].y);
  }
  p_t aa {minx, miny};
  p_t bb {maxx, maxy};
  return {aa, bb};
}
