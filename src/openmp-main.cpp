#include "matrix.h" /* templated matrix class    */ 
#include "darray.h" /* templated array class     */ 
#include <iostream> /* cout, cin, etc...         */  
#include <omp.h>    /* openmp */  
#include <string_view> 

// multiply function prototype
template <typename T> void yAx(const Matrix<T> &A, const Darray<T> &x, Darray<T> &y);  

/* program entry point */ 
int main(int argc, char *argv[]) {

  // grid sizes
  int M = 5;  /* global rows */
  int N = 5;  /* global cols */
 
 // openmp vars
  double tempval; // private thread var for the loop 
  int i, j;       // private thread var for the loop   
  int nthreads = omp_get_max_threads();  

  // check if we need to change size/threads from terminal args 
  if(argc == 4)
  {
	 M = atoi(argv[1]); 
	 N = atoi(argv[2]); 
  	 nthreads = atoi(argv[3]); // set threads at runtime  
  	 omp_set_num_threads(nthreads);     // ensure this amount of threads is set 
  } 

  // declare data structures */ 
  Matrix<int> A(M, N);  /* no global matrix is actually created */ 
  std::string_view Aname = "A"; 
  Darray<int> x(N); 
  std::string_view xname = "x";  
  Darray<int> y(M); 
  std::string_view yname = "y"; 
  
  // init with values  
  A.fillMatInt();       // fill A
  x.fillDarrayInt(); // Fill X 
  
  double start_timer = omp_get_wtime(); // measure yax 
  #pragma omp parallel for private(tempval, i, j)  
  for (i = 0; i < A.Rows(); ++i) {
	  tempval = 0;
      for (j = 0; j < A.Cols(); ++j) {
      tempval += A(i, j) * x(j);
      }
      y(i) = tempval;
  }
  double yAx_time = omp_get_wtime() - start_timer;
  
   // print if size is small  
  if(M*N <= 100)
  {
    A.printNameAndMat(Aname); 
	x.printNameAndArray(xname);
    std::cout << "\n"; 
    y.printNameAndArray(yname); // for checking sol
  }
 
  std::cout << "\nyAx took: " <<  yAx_time << " seconds" << "\nto compute A(" << M << "," << N << ") * x(" << N << ")"; 
  std::cout << "\nwith " << nthreads  << " OpenMP Threads" << std::endl; 
  
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

/* Computation for solution 2 (before reduce) */
template <typename T> 
void xIDy( Matrix<T> &id_A, Darray<T> &y, Darray<T> &x)
{
  for (int i = 0; i < id_A.Rows(); ++i) {
    auto tempval = 0;
    for (int j = 0; j < id_A.Cols(); ++j) {
      tempval += id_A(i, j) * y(i);
      }
      x(i) = tempval; 
  }
}
