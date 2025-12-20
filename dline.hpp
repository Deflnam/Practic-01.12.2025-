#ifndef DLINE_HPP
#define DLINE_HPP
#include "IDraw.hpp"

namespace top
{
  struct DLine : IDraw
  {
    DLine(int x, int y, int len);
    p_t begin() const override;
    p_t next (p_t p) const override;
    p_t start;
    int length;
  };
}
#endif
