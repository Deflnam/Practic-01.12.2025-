#include "canvas.hpp"
#include <iostream>

char* top::buildCanvas(Frame_t fr, char fill)
{
  char* cnv = new char [rows(fr) * cols(fr)];
  for (size_t i = 0; i < rows(fr) * cols(fr); ++i)
  {
    cnv[i] = fill;
  }
  return cnv;
}

void top::paintCanvas(char* cnv, Frame_t fr, p_t* ps, size_t k, char f)
{
  for (size_t i = 0; i < k; ++i)
  {
    int dx = ps[i].x - fr.leftBott.x;
    int dy = fr.rightTop.y - ps[i].y;
    cnv[dy * cols(fr) + dx] = f;
  }
}

void top::printCanvas(char* cnv, Frame_t fr)
{
  for (size_t i = 0; i < rows(fr); ++i)
  {
    for (size_t j = 0; j < cols(fr); ++j)
    {
      std::cout << cnv[i * cols(fr) + j];
    }
      std::cout<< '\n';
  }
}
