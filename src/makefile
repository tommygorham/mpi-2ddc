INCLUDE=../include

all: runmpi runmpidemo runomp runserial  

runmpi: mpi-2ddc-main.cpp $(INCLUDE)/matrix.h $(INCLUDE)/darray.h
	mpic++ -I $(INCLUDE) -std=c++17 -Wall mpi-2ddc-main.cpp -o runmpi 

runmpidemo: mpi-2ddc-5x5demo.cpp $(INCLUDE)/matrix.h $(INCLUDE)/darray.h
	mpic++ -I $(INCLUDE) -std=c++17 -Wall mpi-2ddc-5x5demo.cpp -o runmpidemo  

runomp: openmp-main.cpp $(INCLUDE)/matrix.h $(INCLUDE)/darray.h
	g++ -I $(INCLUDE) -std=c++17 -Wall openmp-main.cpp -o runomp -fopenmp 

runserial: serial.cpp $(INCLUDE)/matrix.h $(INCLUDE)/darray.h 
	g++ -I $(INCLUDE) -std=c++17 -Wall serial.cpp -o runserial 

clean: 
	rm runmpi runmpidemo runomp runserial  
