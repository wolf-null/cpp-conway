cmake_minimum_required(VERSION 3.23)
project(cpp__CONWAY)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        cpp__CONWAY
        main.cpp lib/topology/node_tests.h lib/indices/property.h lib/indices/index_model.h lib/indices/ij.h lib/indices/neighborhood_model.h lib/indices/neighborhood_models/conway.h  lib/indices/network_builders/conway.h lib/indices/index_models/taxicab_padding.h)

include_directories(lib)