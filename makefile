all: runmpi runserial 

runmpi: mpi-2ddc-main.cpp matrix.h darray.h
	mpic++ -std=c++17 -Wall mpi-2ddc-main.cpp -o runmpi 
runserial: serial.cpp matrix.h darray.h 
	g++ -std=c++17 -Wall serial.cpp -o runserial 
