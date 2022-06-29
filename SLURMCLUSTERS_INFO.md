# slurm-clusters
This repository is for storing and recalling common cluster computing practices when submitting MPI jobs with slurm 
 
In particular, the examples depicted are denoting the difference between executing MPI codes on one node vs multiple nodes a Linux Cluster.  

When Using Multiple Nodes: In SLURM multiple nodes can be grouped into **partitions** which are sets of nodes with associated limits for wall-clock time, job size, etc. These limits are hard limits for the jobs and can not be overruled. The defined partitions can overlap, i.e. one node might be contained in several partitions.
To tell the code to excute on a certain partition, add this line to your slurm script

`SBATCH --parition=<whatever-the-partition-name-is>` 

## Common Slurm Commands 

**sinfo** - List partitions/number of nodes available

**squeue** - Display what jobs are currently running 

**scontrol** show job <jobID> - Get job details
  
**vim job-script.sh** - To create a job script 

**sbatch job-script.sh** - To execute a simple job script 
  
**sbatch --nodes=4 --ntasks=8 ./job-script.sh** - To run an MPI job with 4 nodes and 8 MPI processes

# Common Linux Cluster Commands 
**who**   - display who is logged on currently 
  
**w**     - display who is logged on and what are they doing
  
**users** - list logged in users usernames only
  
**who | grep <username>** - search for a specific user 
  
# Writing slurm scripts
  Has to begin with the following line
 
  #!/bin/bash
 
 Remember to module load, or add to slurm script 
 
 # When Using Sun Grid Engine (not Slurm)
 Similiar to slurm, but it uses 'qstat' commands. E.g., 
   
   module load sge
   
   qstat -f
   
   qstat -u "*"
   
 
 
