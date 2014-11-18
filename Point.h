#ifndef ML_POINT_H
#define ML_POINT_H

namespace ML
{
  struct Point
  {
  Point() : x(0), y(0) {}
  Point(double a, double b) : x(a), y(b) {}
  bool operator<(const Point p) const {
    if (x<p.x)
      return true;
    if (x>p.x)
      return false;
    return y<p.y;
  }
    double x;
    double y;
  };
};

#endif // ML_POINT_H
