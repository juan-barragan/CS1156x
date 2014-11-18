#include"RandomTools.h"

#include<algorithm>
#include<random>
#include<chrono>

static std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
static std::uniform_int_distribution<int> distribution_flip(0,1);

std::vector<double> 
ML::RandomTools::generate_real_numbers(unsigned int n, double a, double b)
{
  std::uniform_real_distribution<double> d_real(a,b);
  std::vector<double> ans(n);
  std::generate(ans.begin(), ans.end(), [&d_real]()->double { return d_real(generator); });
  return ans;
}

std::vector<ML::Point> 
ML::RandomTools::generate_points(unsigned int n, double a, double b)
{
  std::vector<Point> answ(n);
  std::vector<double> values = generate_real_numbers(n<<1, a, b);
  int j=0;
  for(unsigned int i=0; i<values.size(); i+=2, ++j)
    answ[j] = Point(values[i], values[i+1]);

  return answ;
}

int ML::RandomTools::generate_int(int a, int b)
{
  std::uniform_int_distribution<int> dist(a,b);
  return dist(generator);
}

std::set<int> ML::RandomTools::different_sample(int n, int a, int b)
{
  std::set<int> index;
  while(index.size()<n)
    index.insert(generate_int(a,b));

  return index;
}
