/* Program name:  serial.cpp 
 * Friendly name: serial y=Ax 
 * Author:        Thomas Gorham 
 * Directions:    g++ -Wall --std=c++17 serial.cpp -o runserial
 *                ./runserial M N 
 */ 

#include "matrix.h" /* templated matrix class    */ 
#include "darray.h" /* templated array class     */ 
#include <iostream> /* cout, cin, etc...         */  
#include <chrono>   /* for timing                  */ 

#define DEFAULT_INPUT "./serial.cpp"

/* multiply function prototypes, TODO: change to one function & decide on const */
template <typename T> void yAx(const Matrix<T> &A, const Darray<T> &x, Darray<T> &y);  
template <typename T> void xIDy(Matrix<T> &xIDy, Darray<T> &y, Darray<T> &x); 

/* program entry point */ 
int main(int argc, char *argv[]) {
  
  const int M = atoi(argv[1]);  /* global rows */
  const int N = atoi(argv[2]);  /* global cols */
  
  Matrix<int> A(M, N); 
  Darray<int> x(N); 
  Darray<int> y(M);
  
  int rank = 0; // no mpi or mpi rank in this file, but letting var name be the same for now 
  A.fillMatIntRank(rank); // increments fill by 1 with each (i,j) iteration 
  x.fillDarrayInt();  // fill with ones 

  /* do the computation and time */
  auto start_timer = std::chrono::high_resolution_clock::now();
  yAx(A,x,y);  /* this computes: A(m,n) * x(n) = y(m) */ 
  auto end_timer = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> yAx_time = end_timer - start_timer; 
  
  // print solution 
  /* for(int i = 0; i < M; ++i)
  {
      std::cout << "\n" << y(i); 
  }
  */
  std::cout << "\n\nyAx took: " << yAx_time.count() << " seconds" << std::endl; 
  
  return 0; 
}

/* Computation for solution 1 (before reducing with MPI_Allreduce) */ 
template <typename T>
void yAx(const Matrix<T> &A, const Darray<T> &x, Darray<T> &y)
{
  for (int i = 0; i < A.Rows(); ++i) {
    auto tempval = 0;
    for (int j = 0; j < A.Cols(); ++j) {
      tempval += A(i, j) * x(j);
    }
    y(i) = tempval;
  }
}

