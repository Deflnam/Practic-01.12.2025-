#ifndef DOT_HPP
#define DOT_HPP
#include "IDraw.hpp"

namespace top
{
  struct Dot : IDraw 
  {
    Dot(int x, int y);
    ~Dot() override = default;
    p_t begin() const override;
    p_t next(p_t p) const override;
  private:
    p_t o;
  };
}
#endif
