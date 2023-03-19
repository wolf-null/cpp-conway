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
        lib/indices/2d_taxicab/index.h lib/indices/2d_taxicab/padding_policies.h lib/indices/2d_taxicab/assets.h lib/indices/2d_taxicab/selectors.h lib/topology/fabric/make_value_nodes.h lib/indices/2d_taxicab/index_policies.h lib/indices/2d_taxicab/tests/index_policies__test.h)

include_directories(lib)