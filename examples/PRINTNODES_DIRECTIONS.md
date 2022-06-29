# 1) ssh into the head node of a cluster, for example 
ssh yourusername@headnodename

# 2) load GCC and OpenMPI
### _Note: its better practice to explicitly load the version you need_ E.g.,: 

module load gcc/10.2.0

### As opposed to just:  
module load openmpi 

# 3) Compile 01.cpp   

mpic++ 01.cpp -o run_mpi_01

# 4) Submit the slurm job 

sbatch 01_simple_mpi_job_script.sh 

# 5) View the output that was generated 

01-job.out 

## Done! 
