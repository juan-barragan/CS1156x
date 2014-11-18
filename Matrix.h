#ifndef ML_MATRIX_H
#define ML_MATRIX_H

#include<iostream>

namespace ML
{
  template<class T> 
    class Matrix 
    {
    public:
      Matrix();
      Matrix(int, int);
      Matrix(const Matrix&);
      ~Matrix();
  
      inline int columns() const { return columns_; }
      inline int rows() const { return rows_; }
      inline T operator()(int i, int j) const { return *(*(data_+j)+i); }
      inline T& operator()(int i, int j) { return *(*(data_+j)+i); }
    
      Matrix<T>& operator=(const Matrix&);
      Matrix<T>& operator*=(const Matrix&);
      Matrix<T> menor(int, int) const;
      Matrix<T> inverse() const;
      Matrix<T> transpose() const;
      Matrix<T> pseudo_inverse() const;
      T cofactor(int, int) const;
      T determinant() const;
      void dump() const;

    private:
      void copy_from(const Matrix&);
      void clean();
      void allocate();
      
      int rows_;
      int columns_;
      T** data_;
    };

  template<class T>
    Matrix<T>::Matrix() 
    : rows_(0), columns_(), data_(0) 
    { 
    }

  template<class T>
    Matrix<T>::Matrix(int n, int m) 
    : rows_(n), columns_(m) 
    { 
      allocate(); 
    }

  template<class T>
    Matrix<T>::Matrix(const Matrix& r) 
    : rows_(r.rows_), columns_(r.columns_)
    {
      allocate();
      copy_from(r);
    }
  
  template<class T>
    Matrix<T>::~Matrix() 
    { 
      clean(); 
    }

  template<class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& r) 
    {
      if(this != &r) {
	clean();
	rows_ = r.rows_; columns_ = r.columns_;
	allocate();
	copy_from(r);
      }
      return *this;
    }

  template<class T>
    Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m) 
    {
      Matrix<T> answer(rows_, m.columns_);
      for(int i=0; i<rows_; ++i)
	for(int j=0; j<m.columns_; ++j) {
	  double sum(0);
	  for(int k=0; k<columns_; ++k) 
	    sum += (*this)(i,k)*m(k,j);
	  answer(i,j) = sum;
	}
      *this = answer;
      return *this;
    }

  template<class T>
    Matrix<T> Matrix<T>::menor(int m, int n) const
    {
      Matrix<T> answer(rows_-1, columns_-1);
      for(int i=0; i<m; ++i)
	for(int j=0; j<n; ++j)
	  answer(i,j) = (*this)(i,j);
      
      for(int i=m+1; i<rows_; ++i)
	for(int j=0; j<n; ++j)
	  answer(i-1,j) = (*this)(i,j);
      
      for(int i=0; i<m; ++i)
	for(int j=n+1; j<columns_; ++j)
	  answer(i,j-1) = (*this)(i,j);
      
      for(int i=m+1; i<rows_; ++i)
	for(int j=n+1; j<columns_; ++j)
	  answer(i-1,j-1) = (*this)(i,j);
      
      return answer;
    }

  template<class T>
    Matrix<T> Matrix<T>::inverse() const
    {
      Matrix<T> answer(rows_, columns_);
      double det = 1.0/determinant();
      for(int i=0; i<rows_; ++i)
	for(int j=0; j<columns_; ++j)
	  answer(i,j) = det*cofactor(j,i);

      return answer;
    }
  template<class T>
    Matrix<T> Matrix<T>::transpose() const
    {
      Matrix<T> answer(columns_, rows_);
      for(int i=0; i<rows_; ++i)
	for(int j=0; j<columns_; ++j)
	  answer(j,i) = (*this)(i,j);
      
      return answer;
    }

  template<class T>
    Matrix<T> operator*(const Matrix<T>& left, const Matrix<T>& right)
    {
      Matrix<T> tmp(left);
      return tmp *= right;
    }

  template<class T>
    Matrix<T> Matrix<T>::pseudo_inverse() const
    {
      Matrix<T> transposed(this->transpose());
      return (transposed*(*this)).inverse()*transposed;
    }
  
  template<class T>
    T Matrix<T>::cofactor(int n, int m) const
    {
      int sign=((n+m)%2 == 0)?1:-1;
      return sign*(this->menor(m,n)).determinant();
    }

  template<class T>
    T Matrix<T>::determinant() const
    {
      if (rows_ == 1 && columns_ == 1)
	return (*this)(0,0);
      //cassert(rows_ == columns_);
      double sum(0); int sgn(-1); int current(1);
      for(int j=0; j<columns_; ++j) {
	sum += (*this)(0,j)*current*(this->menor(0,j)).determinant();
	current *= sgn;
      }
      return sum;
    }

  template<class T>
  void Matrix<T>::dump() const {
    for(int i=0; i<rows_; ++i) {
      for(int j=0; j<columns_; ++j)
        std::cout<<(*this)(i,j)<<",";
      std::cout<<"\n";
    }
  }

  // Implementation stuff, private members
  template<class T>
    void Matrix<T>::copy_from(const Matrix<T>& r)
    {
      for(int i=0; i<rows_; ++i)
	for(int j=0; j<columns_; ++j)
	  (*this)(i,j) = r(i,j);
    
      //int tSize = sizeof(T);
      //for(int j=0; j<columns_; ++j)
      //memcpy(data_[j], r.data_[j], tSize);
    }

  template<class T>
    void Matrix<T>::clean()
    {
      for(int i=0; i<columns_; ++i)
	delete[] data_[i];
      delete[] data_;
    }

  template<class T>
    void Matrix<T>::allocate()
    {
      data_ = new T*[columns_];
      for(int i=0; i<columns_; ++i)
	data_[i] = new T[rows_];
    }
}; // ML namespace

#endif // ML_MATRIX_H
