/* Program name:  mpi-2ddc-main.cpp 
 * Friendly name: MPI 2D domain decomposition for y=Ax 
 * Author:        Thomas Gorham 
 * Directions:    make
 *                mpirun  -np <P*Q> ./run M N P Q 
 */ 

#include "matrix.h" /* templated matrix class    */ 
#include "darray.h" /* templated array class     */ 
#include <iostream> /* cout, cin, etc...         */  
#include <mpi.h>    /* message passing interface */  

/* multiply function prototypes, TODO: change to one function & decide on const */
template <typename T> void yAx(const Matrix<T> &A, const Darray<T> &x, Darray<T> &y);  
template <typename T> void xIDy(Matrix<T> &xIDy, Darray<T> &y, Darray<T> &x); 

/* program entry point */ 
int main(int argc, char *argv[]) {
  
  /* mpi variables */
  int row_rank, col_rank, size, world_rank, node_name_len;
  char node_name[MPI_MAX_PROCESSOR_NAME]; /* specifier for the physical node name*/ 

  /* timing variables */
  double start_timer;

  /* grid sizes to be run with P*Q MPI Processes via -np at runtime */
  const int M = 1024;  /* for CMD, use: atoi(argv[1])   global rows */
  const int N = 1024;                                 /* global cols */
  const int P = 2;                                    /* process rows */
  const int Q = 2;                                    /* process cols */

  /* start mpi */
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(node_name, &node_name_len); /* physical node where the processes are executing */ 

  /* calculate local dims to initialize local data */
  int MdivP = M / P;
  int NdivQ = N / Q;
  int MmodP = M % P;
  int NmodQ = N % Q;
  int local_row = world_rank / Q;
  int local_col = world_rank % Q;
  int i_increment = M / P; /* every rank increment this many rows globally */
  int j_increment = N / Q; /* every rank increment this many cols globally */

  /* create 2 new communicators for local 2d domain decomposition */
  MPI_Comm row_comm;
  MPI_Comm col_comm;

  /* each process in communicator calculate local matrix dims (m,n) */ 
  MPI_Comm_split(MPI_COMM_WORLD, local_row, world_rank, &row_comm);
  MPI_Comm_split(MPI_COMM_WORLD, local_col, world_rank, &col_comm);
  int m, n; /* shape of matrix in each mpi process grid */ 
  if (local_row < P - 1) { m = MdivP; } /* if everything divides evenly set local rows */ 
  else { m = MdivP + MmodP; } /* if there are remaining rows, add whats left */ 
  /* same logic here for local cols */ 
  if (local_col < Q - 1) { n = NdivQ; } 
  else { n = NdivQ + NmodQ; }
  
  /* to access ranks in communicators */
  MPI_Comm_rank(row_comm, &row_rank); 
  MPI_Comm_rank(col_comm, &col_rank); 

  /* declare data structures */ 
  Matrix<int> A(m, n);  /* no global matrix is actually created */ 
  Darray<int> x(n); 
  Darray<int> y(m); 
  Matrix<int> id_A(m, n); /* id matrix for xIDy function */

  /* initialize matrix A, each sub-domain will begin with the value of the mpi_rank */   
  A.fillMatIntRank(world_rank);  

  //process row 0 (node 0) make Darray x 
  if (local_row == 0) { x.fillDarrayInt(); } 

  /* ranks broadcast their local Darray x with to other nodes across columns */
  MPI_Bcast(x.getDarray(), n, MPI_DOUBLE, 0, col_comm);
  
  /* do the computation and time */
  MPI_Barrier(MPI_COMM_WORLD); // sync before timing 
  start_timer = MPI_Wtime(); 
  yAx(A,x,y);  /* this computes: A(m,n) * x(n) = y(m) */ 
  MPI_Barrier(MPI_COMM_WORLD); // ensure every process has finished computation 
  double yAx_time = MPI_Wtime() - start_timer; // via pg. 105 of "Using MPI, 3rd Edition"
   
 /* redistribute y back into x with identity matrix, second param can also be &y(0) */ 
  MPI_Allreduce(MPI_IN_PLACE, y.getDarray(), m, MPI_INT, MPI_SUM, row_comm); /* send buf same as receive */
  /* SOLUTION1: vector y is stored in each process row (or node row)  */ 
  // y.printDarray(node_name); 

  /* fill identity matrix appropriately to redistribute y back into x */ 
  i_increment = M / P; /* every rank increment this many rows globally */
  j_increment = N / Q; /* every rank increment this many cols globally */
  for (int local_i = 0; local_i < m; ++local_i) {
    for (int local_j = 0; local_j < n; ++local_j) {
      int global_i = (i_increment * local_row + local_i);
      int global_j = (j_increment * local_col + local_j);
      if (global_i == global_j) {
        id_A(local_i, local_j) = 1;
      } else
        id_A(local_i, local_j) = 0;
    }
  }

  /* do the computation */  
  xIDy(id_A, y, x); /* this computes: y(m) * id_A(m,n) = x(n); */ 
  
 /* collective to also have solution stored in every process col via the column communicator group */ 
  MPI_Allreduce(MPI_IN_PLACE, x.getDarray(), n, MPI_INT, MPI_SUM, col_comm);  
  /* SOLUTION2: */ // x.printDarray(node_name); 

  /* print time from rank 0 because very little deviation with square matrices due to load balancing */ 
  if(world_rank == 0)
  {
      std::cout <<"\nyAx took: " <<  yAx_time << " seconds" << std::endl;  
  }
  /* free mpi sub-communicators */
  MPI_Comm_free(&row_comm); 
  MPI_Comm_free(&col_comm); 
  
  MPI_Finalize(); 
  
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
