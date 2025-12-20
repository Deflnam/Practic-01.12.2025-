#include <iostream>
#include "geom.hpp"
#include "IDraw.hpp"
#include "dot.hpp"
#include "canvas.hpp"
#include "vline.hpp"
#include "hline.hpp"
#include "dline.hpp"
#include "rectangle.hpp"
#include "square.hpp"

int main()
{
  top::IDraw* f[7] = {};
  top::p_t* p = nullptr;
  size_t s = 0;
  char* cnv = nullptr;
  int statusCode = 0;
  try 
  {
    f[0] = new top::Dot(0, 0);
    f[1] = new top::Dot(-1, -5);
    f[2] = new top::Square(7, 7, 3);
    f[3] = new top::VLine(4, 5, 3);
    f[4] = new top::HLine(2, 7, 4);
    f[5] = new top::DLine(-3, 1, 4);
    f[6] = new top::Rectangle(-10, -4, 4, 7);
    for (size_t i = 0; i < 7; ++i) 
    {
      top::getPoints(f[i], &p, s);
    }
    top::Frame_t fr = top::buildFrame(p, s);
    cnv = top::buildCanvas(fr, '.');
    top::paintCanvas(cnv, fr, p, s, 'o');
    top::printCanvas(cnv, fr);
  } 
  catch(...) 
  {
    statusCode = 1;
  }

  delete f[0];
  delete f[1];
  delete f[2];
  delete f[3];
  delete f[4];
  delete f[5];
  delete f[6];
  delete[] p;
  delete[] cnv;

  return statusCode;
}
