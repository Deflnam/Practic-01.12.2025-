#ifndef HLINE_HPP
#define HLINE_HPP
#include "IDraw.hpp"

namespace top
{
  struct HLine : IDraw 
  {
    HLine(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };
}
#endif
