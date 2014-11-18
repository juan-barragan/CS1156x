#ifndef ML_TUBE_H
#define ML_TUBE_H

#include"Matrix.h"
#include<vector>

namespace ML
{
  class Tube
  {
  public:
    Tube(const std::vector<double>& dimensions);
    double operator()(int, int, int) const;
    double& operator()(int, int, int);
    unsigned int size() const;
    unsigned int depth() const;
    unsigned int columns(int depth) const;
    unsigned int rows(int depth) const;
  private:
    std::vector< ML::Matrix<double> > _values;
  };
};

#endif // ML_TUBE_H
