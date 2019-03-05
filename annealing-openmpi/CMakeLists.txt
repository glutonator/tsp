cmake_minimum_required(VERSION 3.10)
project(annealing_openmpi)

set(CMAKE_CXX_STANDARD 14)

add_executable(annealing_openmpi main.cpp Algorithm.cpp Algorithm.h Graph.cpp Graph.h RandomVector.cpp RandomVector.h)

# Require MPI for this project:
find_package(MPI REQUIRED)
set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
include_directories(${MPI_INCLUDE_PATH})
target_link_libraries(annealing_openmpi ${MPI_LIBRARIES})
