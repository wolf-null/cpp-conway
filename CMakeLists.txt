cmake_minimum_required(VERSION 3.23)
project(cpp__CONWAY)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        cpp__CONWAY
        main.cpp
        lib/topology/abstract_node.h
        lib/topology/node.h
        lib/topology/value_node.h
        lib/topology/summation_node.h
        lib/topology/domain.h
        lib/topology/domain.cpp
        lib/topology/tests/summation_node__test.h
        lib/indices/taxicab_2d_index.cpp
)

include_directories(lib)