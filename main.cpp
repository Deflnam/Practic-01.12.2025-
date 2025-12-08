#include <iostream>

namespace top {
  struct p_t {
    int x,y;
  };

  bool operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }

  bool operator!=(p_t a, p_t b)
  {
    return !(a == b);
  }

  struct Frame_t {
    p_t leftBott, rightTop;
  };

  struct IDraw {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t p) const = 0;
    virtual ~IDraw() = default;
  };

  struct Dot : IDraw {
    Dot(int x, int y) : IDraw(), o{x,y} {}
    ~Dot() override = default;
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t o;
  };

  void extend(p_t** ps, size_t& s, p_t p); 
  void make_f(IDraw** f, size_t k);
  size_t getPoints(IDraw* f, p_t** ps, size_t& s);
  Frame_t buildFrame(const p_t* ps, size_t s);
  char* buildCanvas(Frame_t fr, char);
  void paintCanvas(char* cnv, Frame_t fr, const p_t* ps, size_t k, char f);
  void printCanvas(char* cnv, Frame_t fr);


  size_t rows(Frame_t fr);
  size_t cols(Frame_t fr);

  struct VLine : IDraw {
    VLine(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct HLine : IDraw {
    HLine(int x, int y, int len);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct Square: IDraw {
    Square(int x, int y, int l);
    Square(p_t p, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int len;
  };
}



int main()
{
  top::IDraw* f[3] = {};
  top::p_t* p = nullptr;
  size_t s = 0; 
  char* cnv = nullptr;
  int statusCode = 0;
  try {
    top::make_f(f, 3);
    for (size_t i = 0; i < 3; ++i) {
      top::getPoints(f[i], &p, s);
    }
    top::Frame_t fr = top::buildFrame(p, s);
    cnv = top::buildCanvas(fr, '.');
    top::paintCanvas(cnv, fr, p, s, 'o'); 
    top::printCanvas(cnv, fr);
  } catch(...) {
    statusCode = 1;
  }

  delete f[0];
  delete f[1];
  delete f[2];
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
  f[0] = new top::Dot(0, 0);
  f[1] = new top::Dot(1, -5);
  f[2] = new top::Dot(7, 7);
}


void top::extend(p_t** ps, size_t& s, p_t p)
{
  size_t upd_s = s + 1;
  top::p_t* res = new top::p_t[upd_s];
  for (size_t i = 0; i < s; ++i) {
    res[i] = (*ps)[i];
  }
  res[s] = p;
  delete[] *ps;
  *ps = res;
  s = upd_s; 
}

size_t top::getPoints(IDraw* f, p_t** ps, size_t& s)
{
  p_t p = f->begin();
  extend(ps, s, p);
  p_t current = p;
  p_t next_p = f->next(current);
  
  size_t count = 1;
  while (next_p != f->begin()) {
    extend(ps, s, next_p);
    current = next_p;
    next_p = f->next(current);
    count++;
    if (count > 1000) break; 
  }
  
  return count;
}

top::Frame_t top::buildFrame(const p_t* ps, size_t s)
{
  if (!s) {
    throw std::logic_error("No points");
  }
  int minx = ps[0].x, maxx = ps[0].x;
  int miny = ps[0].y, maxy = ps[0].y;
  for (size_t i = 1; i < s; ++i) {
    if (ps[i].x < minx) minx = ps[i].x;
    if (ps[i].x > maxx) maxx = ps[i].x;
    if (ps[i].y < miny) miny = ps[i].y;
    if (ps[i].y > maxy) maxy = ps[i].y;
  }
  p_t aa {minx, miny};
  p_t bb {maxx, maxy};
  return {aa, bb};
}

size_t top::rows(Frame_t fr)
{
  return fr.rightTop.y - fr.leftBott.y + 1;
}

size_t top::cols(Frame_t fr)
{
  return fr.rightTop.x - fr.leftBott.x + 1;
}

char* top::buildCanvas(Frame_t fr, char fill)
{
  size_t r = top::rows(fr);
  size_t c = top::cols(fr);
  char* newcanws = new char[r * c];
  for (size_t i = 0; i < r * c; ++i) {
    newcanws[i] = fill;
  }
  return newcanws;
}


void top::paintCanvas(char* cnv, Frame_t fr, const p_t* ps, size_t k, char f)
{
  size_t c = top::cols(fr);
  for (size_t i = 0; i < k; ++i) {
    int dx = ps[i].x - fr.leftBott.x;
    int dy = fr.rightTop.y - ps[i].y;
    if (dx >= 0 && dx < (int)c && dy >= 0 && dy < (int)top::rows(fr)) {
      cnv[dy * c + dx] = f;
    }
  }
}

void top::printCanvas(char* cnv, Frame_t fr)
{
  size_t r = top::rows(fr);
  size_t c = top::cols(fr);
  for (size_t i = 0; i < r; ++i) {
    for (size_t j = 0; j < c; ++j) {
      std::cout << cnv[i * c + j];
    }
    std::cout << '\n';
  }
}

top::p_t top::Dot::begin() const
{
  return o;
}

top::VLine::VLine(int x, int y, int len) : IDraw(), start{x,y}, length(len)
{
  
}

top::p_t top::VLine::begin() const
{
  return start;
}

top::p_t top::VLine::next(p_t p) const
{
  if (p.y == start.y + length - 1) {
    return start;
  }
  if (length > 0) {
    return p_t{start.x, p.y + 1};
  }
  return p_t{start.x, p.y - 1};
}

top::HLine::HLine(int x, int y, int len) : IDraw(), start{x, y}, length(len)
{
  
  
}

top::p_t top::HLine::begin() const
{
  return start;
}

top::p_t top::HLine::next(p_t p) const
{
  if (p.x == start.x + length - 1) {
    return start;
  }
  if (length > 0) {
    return p_t{p.x + 1, start.y};
  }
  return p_t{p.x - 1, start.y};
}

top::Square::Square(int x, int y, int l):
  IDraw(),
  start{x, y},
  len(l)
{

}

top::Square::Square(p_t p, int l) : start{p.x, p.y}, len(l)
{
  

}

top::p_t top::Square::begin() const
{
  return start;
}

top::p_t top::Square::next(p_t p) const
{
  if (p.x == start.x && p.y < start.y + len - 1) {
    return {p.x, p.y + 1};
  } else if (p.y == start.y + len - 1 && p.x < start.x + len - 1) {
    return {p.x + 1, p.y};
  } else if (p.x == start.x + len - 1 && p.y > start.y) {
    return {p.x, p.y - 1};
  } else if (p.y == start.y && p.x > start.x) {
    return {p.x - 1, p.y};
  }
  return start; 
}