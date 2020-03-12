cmake_minimum_required(VERSION 3.15)
project(LIPA)

set(CMAKE_CXX_STANDARD 20)

include_directories(Lib)
include_directories(Lib/Armadilio/include)
find_library(BLAS REQURED)
add_executable(LIPA main.cpp Test.cpp Test.h Lib/Armadilio/include/armadillo)
target_link_libraries(LIPA ${CMAKE_SOURCE_DIR}/Lib/libblas.dll ${CMAKE_SOURCE_DIR}/Lib/liblapack.dll)
