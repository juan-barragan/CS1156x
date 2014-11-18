#ifndef ML_PERCEPTRON_H
#define ML_PERCEPTRON_H

#include"Line.h"
#include"Point.h"
#include<vector>
#include<utility>

namespace ML
{
  class Perceptron
  {
  public:
    static std::pair< std::vector<Point>, Line> generate_pla_data(unsigned int n);
    // Solves for the Perceptron Line, starting with g, points must be linearly separable. Returns number of iterations
    static int solve(Line& g, const Line& target, const std::vector<Point>& training);
    static int solveDumping(Line& g, const Line& target, const std::vector<Point>& training);
  };
};


#endif // ML_PERCEPTRON_H
