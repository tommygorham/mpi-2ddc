all : runmpi 

runmpi: mpi-2ddc-main.cpp matrix.h darray.h 
	mpic++ -std=c++17 -Wall mpi-2ddc-main.cpp -o runmpi 
