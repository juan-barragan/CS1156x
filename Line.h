#ifndef ML_LINE_H
#define ML_LINE_H

#include"Point.h"
#include<vector>
#include<utility>
#include<string>

namespace ML
{
  class Line
  {
  public:
    Line(const Point& X1, const Point& X2);
    Line(double a, double b, double c);
    // This builds Minimum Least Squares Line
    Line(const std::vector<Point>& points);
    inline int operator()(const Point& P) const { return (a*P.x + b*P.y + c<0)?-1:1; }
    inline double m() const { return -a/b; }
    inline double i() const { return -c/b; }
    inline double A() const { return a; }
    inline double B() const { return b; }
    inline double C() const { return c; }

    std::pair<std::vector<Point>, std::vector<Point> >
      separate(const std::vector<Point>& points) const;
    // This computes to (a,b,c) + sign*p
    void addWeight(const Point& p, int sign);

  private:
    double a;
    double b;
    double c;
  };
};

#endif // ML_LINE_H
