#include "Line.h"
#include<sstream>

ML::Line::Line(const Point& X1, const Point& X2)
  : a(X2.y - X1.y), b(X1.x - X2.x), c(-b*X1.y - a*X1.x) 
{
}

ML::Line::Line(double x1, double x2, double x3)
  :a(x1), b(x2), c(x3)
{}

ML::Line::Line(const std::vector<Point>& points)
{
  double x_mean(0.);
  double y_mean(0.);
  double xy(0.);
  double xx(0.);
  for(auto p:points) {
    x_mean += p.x;
    y_mean += p.y;
    xy += p.x*p.y;
    xx += p.x*p.x;
  }
  unsigned int n = points.size();
  x_mean /= n;
  y_mean /= n;
  a = (xy - n*x_mean*y_mean)/(xx - n*x_mean*x_mean);
  b = -1.0;
  c = y_mean - a*x_mean;
}

std::pair<std::vector<ML::Point>, std::vector<ML::Point> >
ML::Line::separate(const std::vector<ML::Point>& points) const
{
  std::vector<Point> above;
  std::vector<Point> under;
  for(auto p:points)
    (this->operator()(p)>0)?above.push_back(p):under.push_back(p);
  return std::make_pair(above, under);
}

void ML::Line::addWeight(const Point& p, int sign)
{
  a += sign*p.x;
  b += sign*p.y;
  c += sign;
}

