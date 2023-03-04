cmake_minimum_required(VERSION 3.23)
project(cpp__konway)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp__konway
        main.cpp
        lib/topology/node.cpp
        lib/topology/domain.cpp
        lib/topology/summation_node.cpp
        )

include_directories(lib)