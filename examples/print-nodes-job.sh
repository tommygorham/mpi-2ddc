#!/bin/bash
#SBATCH -J run_print_nodes             # .exe from compiling print-nodes.cpp 
#SBATCH -N 2                           # Execute on 2 nodes in the cluster (you may have more available, but start here if new to mpi)  
#SBATCH -n 4                           # Execute the code with 4 MPI processes 
#SBATCH -t 0:05:00                     # Max time allowed to run, it will be much faster than this 
#SBATCH -o print-nodes-job.out        # .out file generated from running the job with SLURM to see the nodes/ distributed mpi processes  

# Run the job (assumes the .sh is submitted from the same directory)
mpirun ./run_print_nodes
