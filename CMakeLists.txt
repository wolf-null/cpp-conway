cmake_minimum_required(VERSION 3.23)
project(cpp__CONWAY)

set(CMAKE_CXX_STANDARD 20)

# TOPOLOGY --------------

add_library(TOPOLOGY STATIC lib/topology/node.hpp)
set_target_properties(TOPOLOGY PROPERTIES LINKER_LANGUAGE CXX)


# INDICES_BASE ----------

add_library(
        INDICES_BASE STATIC
        lib/indices/property.hpp
        lib/indices/ij.h
        lib/indices/node_container.h
        lib/indices/index_model.h
        lib/indices/ij.cpp
        lib/indices/node_container.cpp
        lib/indices/index_model.cpp
        lib/indices/neighborhood_model.hpp
)

set_target_properties(INDICES_BASE PROPERTIES LINKER_LANGUAGE CXX)


# INDICES_IMPLEMENTATION_CONWAY --------------

add_library(
        INDICES_IMPLEMENTATION_CONWAY STATIC
        lib/indices/index_models/taxicab_with_padding.h
        lib/indices/index_models/taxicab_with_padding.h
        lib/indices/index_models/taxicab_with_padding.cpp
        lib/indices/neighborhood_models/conway_neighbors.hpp
        lib/indices/index_models/taxicab_with_padding.cpp
)
set_target_properties(INDICES_IMPLEMENTATION_CONWAY PROPERTIES LINKER_LANGUAGE CXX)

# DEPENDENCIES --------------

add_executable(
        cpp__CONWAY
        main.cpp
)

target_link_libraries(
        INDICES_IMPLEMENTATION_CONWAY
        INDICES_BASE
)

target_link_libraries(
        cpp__CONWAY
        INDICES_BASE
)

target_link_libraries(
        cpp__CONWAY
        INDICES_IMPLEMENTATION_CONWAY
)

include_directories(lib)