#include <iostream>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <vector>

#include "lib/topology/node.h"
#include "lib/topology/domain.cpp"
#include "lib/topology/summation_node.cpp"
#include "lib/topology/tests/summation_node__test.cpp"

int main()
{

    summation_node_test::_test_neighbour_sum<int, 2>(1, 2);
    return 0;
}
