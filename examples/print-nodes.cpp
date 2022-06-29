#include <iostream> /*to print things*/
#include <mpi.h> /* to use openmpi standard for message passing */ 

int main(int argc, char* argv[]) 
{ 
    MPI_Init(&argc, &argv); /*initialize mpi environment*/ 
    
    // global variables
    int pid, num_mpi_procs, node_name_len; 
    char node_name[MPI_MAX_PROCESSOR_NAME]; /* specifier for the physical node name*/ 

    // collect info 
    MPI_Comm_rank(MPI_COMM_WORLD, &pid); /* get mpi rank aka current process id*/ 
    MPI_Comm_size(MPI_COMM_WORLD, &num_mpi_procs); /* get total number of mpi processes*/ 
    MPI_Get_processor_name(node_name, &node_name_len); /* get physical node name where the processes are executing */ 

    // output
    std::cout << "\nOn Node: " << node_name <<" Process#: " << pid; 
    std::cout << "/" << num_mpi_procs << std::endl; 
    MPI_Finalize(); 
    return 0; 
}
