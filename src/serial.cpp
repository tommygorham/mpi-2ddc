/* Program name:  serial.cpp 
 * How to Run:    ./runserial M N 
 */ 

#include "matrix.h" /* templated matrix class    */ 
#include "darray.h" /* templated array class     */ 
#include <iostream> /* cout, cin, etc...         */  
#include <chrono>   /* for timing                */ 
#include <string_view> 

/* multiply function prototypes, TODO: change to one function & decide on const */
template <typename T> void yAx(const Matrix<T> &A, const Darray<T> &x, Darray<T> &y);  
template <typename T> void xIDy(Matrix<T> &xIDy, Darray<T> &y, Darray<T> &x); 

/* program entry point */ 
int main(int argc, char *argv[]) {
   // grid sizes
   int M = 5; /* global rows */
   int N = 5;  /* global cols */
 
   // check if we need to change size/threads from terminal args 
   if (argc == 3)
   {
      M = atoi(argv[1]); 
	  N = atoi(argv[2]);
   } 
   
   Matrix<int> A(M, N); 
   std::string_view Aname = "A"; 
   Darray<int> x(N); 
   std::string_view xname = "x";  
   Darray<int> y(M);
   std::string_view yname = "y";  
   int rank = 0;           // no mpi or mpi rank in this file, but letting var name be the same for now 
   A.fillMatIntRank(rank); // increments fill by 1 with each (i,j) iteration 
   x.fillDarrayInt();      // fill with ones 
   auto start_timer = std::chrono::high_resolution_clock::now();
   yAx(A,x,y);  // this computes: A(m,n) * x(n) = y(m)  
   auto end_timer = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> yAx_time = end_timer - start_timer; 
  
   if (M*N <= 100)
   {
      A.printNameAndMat(Aname); 
	  x.printNameAndArray(xname);
      std::cout << "\n"; 
	  y.printNameAndArray(yname); // for checking sol
   }
   std::cout <<"\nyAx took: " <<  yAx_time.count() << " seconds" << "\nto compute A(" << M << "," << N << ") * x(" << N << ") in serial" << std::endl; 
   
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

