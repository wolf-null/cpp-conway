cmake_minimum_required(VERSION 3.23)
project(cpp__CONWAY)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        cpp__CONWAY
        main.cpp lib/topology/node_tests.h lib/indices/2d_taxicab/index.h lib/topology/domain.h lib/topology/domain_tests.h)

include_directories(lib)