#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "IDraw.hpp"

namespace top
{
  struct Square: IDraw 
  {
    Square(int x, int y, int l);
    Square(p_t p, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int len;
  };
}
#endif
