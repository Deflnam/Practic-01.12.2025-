#include <iostream>
#include <cstddef>
#include <algorithm>

namespace top 
{
  struct p_t 
  {
    int x, y;
  };

  bool operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }

  bool operator!=(p_t a, p_t b)
  {
    return !(a == b);
  }

  struct Frame_t 
  {
    p_t leftBott, rightTop;
  };

  struct IDraw 
  {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t p) const = 0;
    virtual ~IDraw() = default;
  };

  struct Dot : IDraw 
  {
    Dot(int x, int y) : IDraw(), o{x,y} {}
    ~Dot() override = default;
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t o;
  };

  void extend(p_t** ps, size_t s, p_t p);
  void make_f(IDraw** f, size_t k);
  size_t getPoints(IDraw* f, p_t** ps, size_t& s);
  Frame_t buildFrame(const p_t* ps, size_t s);
  char* buildCanvas(Frame_t fr, char fill);
  void paintCanvas(char* cnv, Frame_t fr, p_t* ps , size_t k, char f);
  void printCanvas(char* cnv, Frame_t fr);

  struct VLine : IDraw 
  {
    VLine(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct HLine : IDraw 
  {
    HLine(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct DiagonalLine : IDraw
  {
    DiagonalLine(int x, int y, int len);
    p_t begin() const override;
    p_t next (p_t p) const override;
    p_t start;
    int length;
  };
  
  struct Rectangle : IDraw
  {
    Rectangle(int x, int y, int a, int b);
    p_t begin() const override;
    p_t next (p_t p) const override;
    p_t start;
    int a_, b_;
  };

  struct Square: IDraw 
  {
    Square(int x, int y, int l);
    Square(p_t p, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int len;
  };

  size_t rows(Frame_t fr);
  size_t cols(Frame_t fr);
}

size_t top::rows(Frame_t fr)
{
  return (fr.rightTop.y - fr.leftBott.y + 1);
}
size_t top::cols(Frame_t fr)
{
  return (fr.rightTop.x - fr.leftBott.x + 1);
}

int main()
{
  top::IDraw* f[7] = {};
  top::p_t* p = nullptr;
  size_t s = 0;
  char* cnv = nullptr;
  int statusCode = 0;
  try 
  {
    top::make_f(f, 7);
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

top::p_t top::Dot::next(p_t p) const
{
  return begin();
}

void top::make_f(IDraw** f, size_t k)
{
  f[0] = new Dot(0, 0);
  f[1] = new Dot(-1, -5);
  f[2] = new Square(7, 7, 3);
  f[3] = new VLine(4, 5, 3);
  f[4] = new HLine(2, 7, 4);
  f[5] = new DiagonalLine(-3, 1, 4);
  f[6] = new Rectangle(-10, -4, 4, 7);
}

void top::extend(p_t** ps, size_t s, p_t p)
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

top::Frame_t top::buildFrame(const p_t* ps, size_t s)
{
  if (!s)
  {
    throw std::logic_error("");
  }
  int minx = ps[0].x, maxx = ps[0].x;
  int miny = ps[0].y, maxy = ps[0].y;
  for (size_t i = 1; i < s; ++i) 
  {
    minx = std::min(minx, ps[i].x);
    maxx = std::max(maxx, ps[i].x);
    miny = std::min(miny, ps[i].y);
    maxy = std::max(maxy, ps[i].y);
  }
  p_t aa {minx, miny};
  p_t bb {maxx, maxy};
  return {aa, bb};
}

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

top::p_t top::Dot::begin() const
{
  return o;
}

top::VLine::VLine(int x, int y, int len) : IDraw(), start{x,y}, length(len)
{
  if (len == 0) 
  {
    throw std::logic_error("user invalid");
  }
}

top::p_t top::VLine::begin() const
{
  return start;
}

top::p_t top::VLine::next(p_t p) const
{
  if (p.y == start.y + length - 1) 
  {
    return start;
  }
  if (length > 0) 
  {
    return p_t{start.x, p.y + 1};
  }
  return p_t{start.x, p.y - 1};
}

top::HLine::HLine(int x, int y, int len) : IDraw(), start{x, y}, length(len)
{
  if (len == 0) 
  {
    throw std::logic_error("user invalid");
  }
}

top::p_t top::HLine::begin() const
{
  return start;
}

top::p_t top::HLine::next(p_t p) const
{
  if (p.x == start.x + length - 1) 
  {
    return start;
  }
  if (length > 0) 
  {
    return p_t{p.x + 1, start.y };
  }
  return p_t{p.x - 1, start.y };
}

top::Square::Square(int x, int y, int l):
  IDraw(), start{x, y}, len(l)
{
  if (len <= 0) 
  {
    throw std::invalid_argument("length can not be <= 0");
  }
}

top::DiagonalLine::DiagonalLine(int x, int y, int len) : IDraw(), start{x, y}, length(len)
{
  if (len <= 0)
  {
    throw std::logic_error("user invalid");
  }
}

top::p_t top::DiagonalLine::begin() const
{
  return start;
}

top::p_t top::DiagonalLine::next(p_t p) const
{
  if (p.x - start.x == p.y - start.y)
  {
    if (p.x == start.x + length - 1 && p.y == start.y + length - 1)
    {
      return start;
    }
    return {p.x + 1, p.y + 1};
  }
  return start;
}

top::Square::Square(p_t p, int l):
  Square(p.x, p.y, l)
{}

top::p_t top::Square::begin() const
{
  return start;
}

top::p_t top::Square::next(p_t p) const
{
  if (p.x == start.x && p.y < start.y + len - 1) 
  {
    return {p.x, p.y + 1};
  } 
  else if (p.y == start.y + len - 1 && p.x < start.x + len - 1) 
  {
    return {p.x + 1, p.y};
  } 
  else if (p.x == start.x + len - 1 && p.y > start.y) 
  {
    return {p.x, p.y - 1};
  } 
  else if (p.y == start.y && p.x > start.x) 
  {
    return {p.x - 1, p.y};
  }
  return start;
}

top::Rectangle::Rectangle(int x, int y, int a, int b) : IDraw(), start{x, y}, a_(a), b_(b)
{
  if (a <= 0 || b <= 0)
  {
    throw std::logic_error("user invalid");
  }
}

top::p_t top::Rectangle::begin() const
{
  return start;
}

top::p_t top::Rectangle::next(p_t p) const
{
  if (p.x == start.x && p.y < start.y + b_ - 1)
  {
    return {p.x, p.y + 1};
  }
  else if (p.y == start.y + b_ - 1 && p.x < start.x + a_ - 1)
  {
    return {p.x + 1, p.y};
  }
  else if (p.x == start.x + a_ - 1 && p.y > start.y)
  {
    return {p.x, p.y - 1};
  }
  else if (p.y == start.y && p.x > start.x)
  {
    return {p.x - 1, p.y};
  }
  return start;
}