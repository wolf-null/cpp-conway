#include <iostream>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <vector>

#include "lib/topology/node.h"
#include "lib/topology/node_tests.h"

#include <iostream>


int main(int argc, char* argv[]) {
    std::cout << "x_x\n";
    topology::NodeTest::test_neighbor_destruction();
    return 0;
}