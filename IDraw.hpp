#ifndef IDRAW_HPP
#define IDRAW_HPP
#include <cstddef>
#include "geom.hpp"

namespace top
{
  struct IDraw
  {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t p) const = 0;
    virtual ~IDraw() = default;
  };
  size_t getPoints(IDraw* f, p_t** ps, size_t& s);
}
#endif
