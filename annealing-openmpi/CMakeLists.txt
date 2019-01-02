cmake_minimum_required(VERSION 3.13)
project(annealing_openmpi)

set(CMAKE_CXX_STANDARD 14)

add_executable(annealing_openmpi main.cpp Algorithm.cpp Algorithm.h Graph.cpp Graph.h RandomVector.cpp RandomVector.h)