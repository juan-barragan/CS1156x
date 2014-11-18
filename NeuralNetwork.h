#ifndef ML_NEURAL_NETWORK_H
#define ML_NEURAL_NETWORK_H

#include"Sigmoid.h"
#include"Tube.h"
#include<vector>

namespace ML
{
  class NeuralNetwork
  {
  public:
    NeuralNetwork(const std::vector<double>& dimensions, const Sigmoid& s);
    void fillUpWith(double a, double b);
  private:
    Tube _t;
    std::vector< std::vector<double> > _nodes;
    const Sigmoid& _s;
  };
};

#endif // ML_NEURAL_NETWORK_H
