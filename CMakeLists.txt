cmake_minimum_required(VERSION 3.10)
project(mpi2ddc CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall)
include_directories(include/)

# Find Required Dependencies
find_package(MPI REQUIRED)
include_directories(${MPI_CXX_INCLUDE_PATH})

# Find Optional Dependencies
find_package(OpenMP)

# MPI executables
add_executable(runmpi src/mpi-2ddc-main.cpp)
target_link_libraries(runmpi ${MPI_CXX_LIBRARIES})

add_executable(runmpidemo src/mpi-2ddc-5x5demo.cpp)
target_link_libraries(runmpidemo ${MPI_CXX_LIBRARIES})

# OpenMP executable
if(OpenMP_FOUND)
  add_executable(runomp src/openmp-main.cpp)
  target_link_libraries(runomp OpenMP::OpenMP_CXX)
endif() 

# Serial executable
add_executable(runserial src/serial.cpp)
