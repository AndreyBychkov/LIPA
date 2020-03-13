cmake_minimum_required(VERSION 3.15)
project(LIPA)

set(CMAKE_CXX_STANDARD 20)

include_directories(armadillo-code/include)
add_executable(LIPA main.cpp armadillo-code/include/armadillo optimization.cpp optimization.hpp)
target_link_libraries(LIPA ${CMAKE_SOURCE_DIR}/OpenBLAS/build/lib/libopenblas.a)