cmake_minimum_required(VERSION 3.23)
project(cpp__konway)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        cpp__konway
        main.cpp
        lib/topology/node.cpp
        lib/topology/domain.cpp
        lib/topology/summation_node.cpp
        lib/indices/taxicab_2d_index.cpp
        lib/topology/node.h
        lib/topology/domain.h
        lib/topology/tests/summation_node__test.cpp
)

include_directories(lib)