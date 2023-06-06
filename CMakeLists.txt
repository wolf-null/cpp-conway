cmake_minimum_required(VERSION 3.23)
project(cpp__CONWAY)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        cpp__CONWAY
        main.cpp lib/topology/node__tests.hpp lib/indices/property.hpp lib/indices/index_model.hpp lib/indices/ij.hpp lib/indices/neighborhood_model.hpp lib/indices/neighborhood_models/conway_neighbors.hpp lib/indices/network_builders/conway_netbuilder.hpp lib/indices/index_models/taxicab_with_padding.hpp)

include_directories(lib)