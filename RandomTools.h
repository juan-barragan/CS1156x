#ifndef ML_RANDOM_TOOLS_H
#define ML_RANDOM_TOOLS_H

#include"Point.h"
#include<set>
#include<vector>
#include<functional>

namespace ML
{
  class RandomTools
  {
  public:

    static std::vector<double> generate_real_numbers(unsigned int n, double a, double b);
    static std::vector<Point> generate_points(unsigned int n, double a, double b);
    // generate x, a<= x <=b
    static int generate_int(int a, int b);
    // generates n different numbers between a and b. should be b-a>=n, otherwise never end loop...
    static std::set<int> different_sample(int n, int a, int b);
  };
};

#endif // ML_RANDOM_TOOLS_H
