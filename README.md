# mpi-2ddc

[This program](https://github.com/tommygorham/mpi-2ddc/blob/main/src/mpi-2ddc-main.cpp) is a two-dimensional domain decomposition using MPI to communicate and reduce matrix & array computations in the equation y=Ax. Essentially, in using MPI, we can take the serial equation and break it into smaller chunks to have each processor or node do less work, therefore, speeding up our computation. 

# 4-Core Standalone Computer Speedup with 4 MPI Processes 

<p align="center">
<img src="https://github.com/tommygorham/mpi-2ddc/blob/main/results/standalone_4core_speedup_16k16k.png" height="300px" />
</p>

```math
Amdahl's Law     = Serial Time / Parallel Time 
parallel speedup = 3.30635s / .792755s
parallel speedup = 4.17078s
```

# Details 
**Serial Equation:**   A(M,N) * x(N) = y(M)  (where M = Global Matrix Rows, N = Global Matrix Cols) 

Becomes 

**MPI 2DDC Equation:** A(m,n) * x(n) = y(m) (where m = Logical MPI Grid Rows, n = Logical MPI Grid Cols)

In the MPI eq., (m,n) are local to mpi processes, representing their 2D sub-domain 

Currently, the default sizes are: 

M = 16384

N = 16384

P = 2

Q = 2

Meaning the number of processes to pass mpirun -np should be 4 for now

### Compile: make 

### Run: mpirun -np 4 ./runmpi

M and N have only been tested with square martices, so its best to ensure these parameters are the same. 

## Important

If you change the sizes in the source code, make sure that P*Q = the number of processors passed to the -np flag. 

      E.g., mpirun -np 4 ./runmpi 1024 1024 2 2 
      or,   mpirun -np 8 ./runmpi 1024 1024 4 4 
The default way to run the code is: 

      mpirun -np 4 ./runmpi 
      ./runserial 
If you have 4 processor cores available, you can just run 

      mpirun ./runmpi 

_Note:_ The two terminal commands above are just defaults for running [mpi-2ddc-main.cpp](https://github.com/tommygorham/mpi-2ddc/blob/main/mpi-2ddc-main.cpp)
To compile the visual 5x5 demo, run the following commands: 
* g++ -Wall mpi-2ddc-5x5demo.cpp -o rundemo   
* mpirun -np 4 ./rundemo


# Source Code Files Info 

[serial.cpp](https://github.com/tommygorham/mpi-2ddc/blob/main/serial.cpp) As a baseline for performance evaluation. 

[mpi-2ddc-main.cpp](https://github.com/tommygorham/mpi-2ddc/blob/main/mpi-2ddc-main.cpp): main file for running with make comand and either using mpirun or submitting [test-job.sh](https://github.com/tommygorham/mpi-2ddc/blob/main/test-job.sh) to a cluster scheduler. 

[mpi-2ddc-5x5demo.cpp](https://github.com/tommygorham/mpi-2ddc/blob/main/mpi-2ddc-5x5demo.cpp): is here to provide a visual demonstration of the domain decomposition. 

Ideal use case for this file: 

* Comment out [line 105](https://github.com/tommygorham/mpi-2ddc/blob/main/mpi-2ddc-5x5demo.cpp#:~:text=y.printDarray(node_name)%3B) and then uncomment the [two lines of code marked DEMO1](https://github.com/tommygorham/mpi-2ddc/blob/main/mpi-2ddc-5x5demo.cpp#:~:text=//%20DEMO1%3A%20%20if,A.printMat(node_name)%3B) (line 87-88). Now,  recompile and run to view how A(5,5) gets mapped to A(m,n) where each MPI process has its own local value for both m,n.  

* Add the comments back to these lines and uncomment [lines 95-96](https://github.com/tommygorham/mpi-2ddc/blob/main/mpi-2ddc-5x5demo.cpp#:~:text=//%20DEMO2%3A%20if,x.printDarray(node_name)%3B) to view the dimensions of Vector(x) and what nodes/mpi processes have the respectives values. 

* Lastly, uncomment the [line 105](https://github.com/tommygorham/mpi-2ddc/blob/main/mpi-2ddc-5x5demo.cpp#:~:text=y.printDarray(node_name)%3B) to view how the final solution is communicated and stored

