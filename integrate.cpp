#include "integrate.h"
#include<cmath>
#include<iostream>

double ML::Integral::montecarlo(const Functional& f, double a, double b, int n)
{
  std::vector<Point> points = RandomTools::generate_points(n, a, b);
  int sumplus=0;
  int summinus=0;
  for(int i=0; i<n; ++i) {
    double y = f(points[i].x);
    if (y>0)
      if (points[i].y>=0 && points[i].y<=y) ++sumplus;
      else
	;
    else
      if (points[i].y<=0 && points[i].y>=y) ++summinus;
  }
  std::cout<<sumplus<<std::endl;
  return (double)(sumplus - summinus)/n;
}

double ML::Integral::trapezoidal(const Functional& f, double a, double b, int n)
{
  const double delta = (b-a)/n;
  double t = a;
  double sum = 0;
  for(int k=1; k<n; ++k) {
    t += delta;
    sum += f(t) ;
  }
  sum += (f(a)+f(b))/2.0;
  return (b-a)*sum/n;
}

double ML::Integral::simpson(const Functional& f, double a, double b, int n)
{
  const double delta = (b-a)/n;
  double t = a+delta;
  double sum = f(a)+f(b);

  for(int i=1; i<n; i+=2) {
    sum += 4 * f(t);
    t += 2*delta;
  }
  t = a;
  for(int i=2; i<n-1; i+=2) {
    t += 2*delta;
    sum += 2 * f(t);
  }
 
  return sum * delta / 3;
}
