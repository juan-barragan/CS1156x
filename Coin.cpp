#include "Coin.h"
#include "RandomTools.h"

int ML::Coin::_counter = 0;

ML::Coin::Coin() // it supposes 10 flips 
{
  int flipped = RandomTools::generate_int(0,1023);
  _frequency = (double)popcount_3(flipped)/10.0;
}

int ML::Coin::popcount_3(uint64_t x)
{
  x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
  x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits 
  x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
  return (x * h01)>>56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ... 
}

std::tuple<double, double, double> ML::coin_frequency(int tryouts, int num_coins)
{
  double frequencyFirst(0.);
  double frequencyRand(0.);
  double frequencyMin(0.);
  for(int i=0; i<tryouts; ++i) {
    std::vector<Coin> portfolio(num_coins);
      int min(0);
      double minFrequency = 1;
      for(int i=0; i<num_coins; ++i) {
        Coin c = portfolio[i];
        if (c.headFrequency() < minFrequency) {
          minFrequency = c.headFrequency();
          min = i;
        }
      }
      Coin c1 = portfolio[0];
      Coin crand = portfolio[RandomTools::generate_int(0,num_coins-1)];
      Coin cmin = portfolio[min];
      frequencyFirst += c1.headFrequency();
      frequencyRand += crand.headFrequency();
      frequencyMin += cmin.headFrequency();
  }
  return std::make_tuple(frequencyFirst/tryouts, frequencyRand/tryouts, frequencyMin/tryouts);
}
