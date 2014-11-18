#ifndef ML_CUBE_H
#define ML_CUBE_H

namespace ML
{
  class Cube
  {
  public:
  Cube(unsigned int m, unsigned int n, unsigned int o) :
    rows_(m), columns_(n), depth_(o), values_(0) {
      for(unsigned int k=0; k<depth_; ++k) {
	values_[k] = new T*[columns_];
	for(unsigned int j=0; j<columns_; ++j)
	  values_[k][j] = new T[rows_];
      }
      for(unsigned int k=0; k<depth_; ++k)
	for(unsigned int j=0; j<columns_; ++j)
	  for(unsigned int i=0; i<rows_; ++i)
	    values_[k][j][i] = 0;
      
    }

  inline T& operator()(unsigned int i, unsigned int j, unsigned int k)
  { return values_[k][j][i]; }

  inline const T& operator()(unsigned int i, unsigned int j, unsigned int k) const
  { return values_[k][j][i]; }

  ~Cube() {
    for(unsigned int k=0; k<depth_; ++k) {
      for(unsigned int j=0; j<columns_; ++j)
        delete[] values_[k][j];
      delete[] values_[k];
    }
    delete[] values_;
  }


  const unsigned int rows_;
  const unsigned int columns_;
  const unsigned int depth_;
    
  private:
  double*** values_;;
  };
};

#endif // ML_CUBE_H
