#ifndef ML_SIGMOID_H
#define ML_SIGMOID_H

namespace ML
{
  class Sigmoid
  {
  public:
    Sigmoid() {}
    virtual double operator()(double x) const = 0;
    virtual double derivative(double x) const = 0;
    virtual ~Sigmoid() {}
  };
};

#endif // ML_SIGMOID_H
