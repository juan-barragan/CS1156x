#include"Perceptron.h"
#include"RandomTools.h"
#include "Visualization.h"
#include<string>

#include<iostream>

std::pair< std::vector<ML::Point>, ML::Line> ML::Perceptron::generate_pla_data(unsigned int n)
{
  std::vector<Point> answ(n);
  std::vector<double> values = RandomTools::generate_real_numbers(2*(n+2), -1, 1);
  int j=0;
  for(unsigned int i=0; i<values.size()-4; i+=2, ++j)
    answ[j] = Point(values[i], values[i+1]);
  int last = values.size()-1;
  return std::make_pair(answ, Line(Point(values[last-3], values[last-2]), Point(values[last-1], values[last])));
}

int ML::Perceptron::solve(ML::Line& g, const ML::Line& target, const std::vector<Point>& training)
{
  bool converge(false);
  int iteration(0);

  while (iteration<1000 && !converge) {
    ++iteration;
    std::vector<Point> rightclassified;
    std::vector<Point> missclassified;
    for(auto p:training)
      if (g(p) != target(p))
        missclassified.push_back(p);
      else
	rightclassified.push_back(p);
    converge = missclassified.size()==0;
    if(!converge) {
      // pick one at random and update g
      int item = RandomTools::generate_int(0, missclassified.size()-1);
      g.addWeight(missclassified[item], target(missclassified[item]));
    }
  }

  return iteration;
}

