#ifndef ML_INTEGRATE_H
#define ML_INTEGRATE_H

#include "RandomTools.h"

namespace ML
{
  class Functional
  {
  public:
    Functional() {}
    virtual double operator()(double) const = 0;
    virtual ~Functional() {}
  protected:
  };

  class Integral{
  public:
    static double montecarlo(const Functional& f, double a, double b, int points);
    static double trapezoidal(const Functional& f, double a, double b, int points);
    static double simpson(const Functional& f, double a, double b, int points);
  };
};

#endif // ML_INTEGRATE_H

