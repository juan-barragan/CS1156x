#include"Tube.h"

ML::Tube::Tube(const std::vector<double>& d)
{
  _values.resize(d.size());
  for(int i=0; i<_values.size()-1; ++i)
    _values[i] = Matrix<double>(d[i], d[i+1]-1);
  _values[d.size()-1] = Matrix<double>(d[d.size()-1], 1);
}
  
double ML::Tube::operator()(int i, int j, int k) const
{
  return _values[k](i,j);
}
double& ML::Tube::operator()(int i, int j, int k)
{
  return _values[k](i,j);
}

unsigned int  ML::Tube::size() const
{
  unsigned int sum(0);
  for(int i=0; i<_values.size(); ++i)
    sum += _values[i].columns()*_values[i].rows();

  return sum;
}

unsigned int  ML::Tube::depth() const
{
  return _values.size();
}

unsigned int ML::Tube::columns(int depth) const
{
  return _values[depth].columns();
}
unsigned int ML::Tube::rows(int depth) const
{
  return _values[depth].rows();
}
