#include <iostream>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <vector>

#include "lib/topology/node.h"
#include "lib/topology/domain.h"
#include "lib/topology/summation_node.h"
#include "lib/topology/tests/summation_node__test.h"

int main()
{

    topology_tests::_test_neighbour_sum<int, 2>(1, 2);
    return 0;
}
