cmake_minimum_required(VERSION 3.22)
project(BigInt)

set(CMAKE_CXX_STANDARD 17)

add_executable(BigInt main.cpp big_int.hpp big_int.cpp)
