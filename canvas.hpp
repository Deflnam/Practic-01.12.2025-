#ifndef CANVAS_HPP
#define CANVAS_HPP
#include <iosfwd>
#include "geom.hpp"

namespace top
{
  char* buildCanvas(Frame_t fr, char fill);
  void paintCanvas(char* cnv, Frame_t fr, p_t* ps , size_t k, char f);
  void printCanvas(char* cnv, Frame_t fr);
}
#endif
