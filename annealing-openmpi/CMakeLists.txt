cmake_minimum_required(VERSION 3.13)
project(annealing_openmpi)

set(CMAKE_CXX_STANDARD 14)

add_executable(annealing_openmpi main.cpp Algorithm.cpp Algorithm.h Graph.cpp Graph.h RandomVector.cpp RandomVector.h)

#OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# Require MPI for this project:
find_package(MPI REQUIRED)
set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
include_directories(${MPI_INCLUDE_PATH})
target_link_libraries(annealing_openmpi ${MPI_LIBRARIES})

#SET(CMAKE_C_COMPILER mpicc)
#SET(CMAKE_CXX_COMPILER mpicxx)