#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<cmath>
#include<utility>

#include"Matrix.h"
#include"RandomTools.h"

std::pair<ML::Matrix<double>, ML::Matrix<double> > load_file(const std::string& file_name)
{
  std::vector<std::string> lines;
  std::ifstream infile(file_name);
  std::string line;
  while(std::getline(infile, line))
    lines.push_back(line);
  // process lines for getting numbers
  ML::Matrix<double> X(lines.size(), 2);
  ML::Matrix<double> Y(lines.size(), 1);
  for(int i=0; i<lines.size(); ++i) {
    std::istringstream iss(lines[i]);
    iss>>X(i,0)>>X(i,1)>>Y(i,0);
  }

  return std::make_pair(X,Y);
}

double f3(double x1, double x2) { return x1*x1; }
double f4(double x1, double x2) { return x2*x2; }
double f5(double x1, double x2) { return x1*x2; }
double f6(double x1, double x2) { return std::abs(x1-x2); }
double f7(double x1, double x2) { return std::abs(x1+x2); }

typedef double (*pf)(double, double);
static pf function_choices[8] = { 0, 0, 0, &f3, &f4, &f5, &f6, &f7 };

std::pair<ML::Matrix<double>, ML::Matrix<double> > build_matrices(const ML::Matrix<double>& X, const ML::Matrix<double>& Y, int k, int upto)
{
  ML::Matrix<double> XX(upto, k+1);
  ML::Matrix<double> YY(upto, 1);

  for(int i=0; i<upto; ++i) {
    YY(i,0) = Y(i,0);
    XX(i,0) = 1;
    XX(i,1) = X(i,0);
    XX(i,2) = X(i,1);
    for(int kk=3; kk<=k; ++kk)
      XX(i,kk) = function_choices[kk](XX(i,1), XX(i,2));
  }

  return std::make_pair(XX,YY);
}
std::pair<ML::Matrix<double>, ML::Matrix<double> > build_matrices_inverted(const ML::Matrix<double>& X, const ML::Matrix<double>& Y, int k, int starting)
{
  ML::Matrix<double> XX(X.rows()-starting, k+1);
  ML::Matrix<double> YY(X.rows()-starting, 1);

  for(int i=0; i<X.rows()-starting; ++i) {
    YY(i,0) = Y(starting+i,0);

    XX(i,0) = 1;
    XX(i,1) = X(starting+i,0);
    XX(i,2) = X(starting+i,1);
    for(int kk=3; kk<=k; ++kk)
      XX(i,kk) = function_choices[kk](XX(i,1), XX(i,2));
  }

  return std::make_pair(XX,YY);
}

ML::Matrix<double> solve(const ML::Matrix<double>& X, const ML::Matrix<double>& Y)
{
  ML::Matrix<double> XT = X.transpose();
  ML::Matrix<double> M = XT*X;

  return (M.inverse()*XT)*Y;
}

double evaluate(double x1, double x2, const ML::Matrix<double>& w, int k)
{
  double sum(w(0,0) + w(1,0)*x1 + w(2,0)*x2);
  for(int kk=3; kk<=k; ++kk)
    sum += w(kk,0)*function_choices[kk](x1, x2);
  return (sum<0)?-1:1;
}

void exercise_1()
{
  auto values = load_file("in.dta");
  auto outValues = load_file("out.dta");
  for(int k=3; k<8; ++k) {
    auto data = build_matrices(values.first, values.second, k, 25);
    auto w = solve(data.first, data.second);
    // validation error
    int missclased(0);
    for(int i=25; i<values.first.rows(); ++i)
      if (values.second(i,0) != evaluate(values.first(i,0), values.first(i,1),w,k))
	++missclased;
    std::cout<<"k = "<<k<<" Validation error "<<(double)missclased/(values.first.rows()-25)<<std::endl;
    // Out error
    int missOut(0);
    for(int i=0; i<outValues.first.rows(); ++i) {
      if (outValues.second(i,0) != evaluate(outValues.first(i,0), outValues.first(i,1),w,k))
     	++missOut;
    }
    std::cout<<"k = "<<k<<" Out error "<<(double)missOut/(outValues.first.rows())<<std::endl;
  }
}

void exercise_3()
{
  auto values = load_file("in.dta");
  auto outValues = load_file("out.dta");
  for(int k=3; k<8; ++k) {
    auto data = build_matrices_inverted(values.first, values.second, k, 25);
    auto w = solve(data.first, data.second);
    // validation error
    int missclased(0);
    for(int i=0; i<25; ++i)
      if (values.second(i,0) != evaluate(values.first(i,0), values.first(i,1),w,k))
     	++missclased;
    std::cout<<"k = "<<k<<" Validation error "<<(double)missclased/(values.first.rows()-25)<<std::endl; //(values.first.rows()-25)
    // Out error
    int missOut(0);
    for(int i=0; i<outValues.first.rows(); ++i) {
      if (outValues.second(i,0) != evaluate(outValues.first(i,0), outValues.first(i,1),w,k))
      	++missOut;
    }
    std::cout<<"k = "<<k<<" Out error "<<(double)missOut/(outValues.first.rows())<<std::endl;
  }
}

void exercise_6()
{
  std::vector<double> e1 = ML::RandomTools::generate_real_numbers(1000000, 0, 1);
  std::vector<double> e2 = ML::RandomTools::generate_real_numbers(1000000, 0, 1);
  double score(0.);
  for(int i=0; i<e1.size(); ++i)
    score += std::min(e1[i], e2[i]);
  std::cout<<"Expected value: "<<score/e1.size()<<std::endl;
}

int main()
{
  exercise_1();
  exercise_3();
  exercise_6();

  return 0;
}
