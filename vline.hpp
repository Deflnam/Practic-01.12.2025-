#ifndef VLINE_HPP
#define VLINE_HPP
#include "IDraw.hpp"
#include <stdexcept>

namespace top {
  struct VLine : IDraw {
    VLine(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
  private:
    p_t start;
    int length;
  };
}
#endif
