#!/bin/bash
#SBATCH -J runmpi                
#SBATCH -N 2                           # Execute on 2 nodes in the cluster  
#SBATCH -n 4                           # Execute the code with 4 MPI processes 
#SBATCH -t 0:05:00                    
#SBATCH -o twonode-ddc-mpi.out        # New output file name to view the difference 

# Run the job (assumes the .sh is sulsbmitted from the same directory)
mpirun ./runmpi  
