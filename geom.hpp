#ifndef GEOM_HPP
#define GEOM_HPP
#include <cstddef>

namespace top
{
  struct p_t 
  {
    int x, y;
  };
  bool operator==(p_t a, p_t b);
  bool operator!=(p_t a, p_t b);
  struct Frame_t 
  {
    p_t leftBott, rightTop;
  };
  size_t rows(Frame_t fr);
  size_t cols(Frame_t fr);
  Frame_t buildFrame(const p_t* ps, size_t s);
}
#endif
