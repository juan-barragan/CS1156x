#include"NeuralNetwork.h"
#include"RandomTools.h"

ML::NeuralNetwork::NeuralNetwork(const std::vector<double>& dimensions, const Sigmoid& s)
  : _t(dimensions), _s(s)
{
  _nodes.resize(dimensions.size());
  for(int i=0; i<_nodes.size(); ++i) {
    _nodes[i].resize(dimensions[i] - 1);
  }
}

void ML::NeuralNetwork::fillUpWith(double a, double b)
{
  std::vector<double> values = RandomTools::generate_real_numbers(_t.size(), a, b);
  unsigned int cursor(0);
  for(int k=0; k<_t.depth(); ++k)
    for(int i=0; i<_t.rows(k); ++i)
      for(int j=0; j<_t.columns(k); ++j)
	_t(i,j,k) = values[cursor++];
}
