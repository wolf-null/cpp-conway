cmake_minimum_required(VERSION 3.23)
project(cpp__CONWAY)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        cpp__CONWAY
        main.cpp lib/topology/node_tests.h lib/indices/property.h lib/indices/2d_taxicab/index_model.h lib/indices/2d_taxicab/index_ij.h)

include_directories(lib)