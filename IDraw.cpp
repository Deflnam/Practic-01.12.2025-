#include "IDraw.hpp"
static void extend(top::p_t** ps, size_t s, top::p_t p)
{
  size_t upd_s = s + 1;
  top::p_t* res = new top::p_t[upd_s];
  if (s > 0 && *ps != nullptr)
  {
    for (size_t i = 0; i < s; ++i)
    {
      res[i] = (*ps)[i];
    }
  }
  res[s] = p;
  delete[] *ps;
  *ps = res;
}
size_t top::getPoints(IDraw* f, p_t** ps, size_t& s)
{
  p_t p = f->begin();
  extend(ps, s, p);
  size_t delta = 1;
  while (f->next(p) != f->begin())
  {
    p = f->next(p);
    extend(ps, s + delta, p);
    delta++;
  }
  return s += delta;
}
