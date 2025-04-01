#!/bin/bash
#SBATCH --job=runserial                
#SBATCH --nodes=1                           # node count  
#SBATCH --ntasks=1                          # tasks across nodes 
#SBATCH --cpus-per-task=1
#SBATCH -t 0:01:00                    
#SBATCH -o serial.out       

# Run the job (assumes the .sh is sulsbmitted from the same directory)
./runserial   
