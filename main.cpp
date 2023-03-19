#include <iostream>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <vector>

#include "lib/topology/node.h"
#include "lib/topology/domain.h"
#include "lib/topology/summation_node.h"
#include "lib/topology/tests/summation_node__test.h"
#include "lib/topology/fabric/make_value_nodes.h"

#include "lib/indices/2d_taxicab/tests/index_policies__test.h"
#include "lib/indices/2d_taxicab/index_policies.h"
#include "lib/indices/2d_taxicab/index.h"



int main()
{
    // topology_tests::_test_neighbour_sum<int, 2>(1, 2);
    //indices_tests::check_index_policy<IndexPolicyLinear>();

    constexpr int h = 5;
    constexpr int w = 10;
    constexpr int length = w * h;
    constexpr int max_neighbours = 8;

    typedef int ValueType;
    ValueType def_val = 0;

    auto* domain = new topology::NodeDomain{};
    topology::make_summation_nodes<max_neighbours, ValueType>(length, domain, def_val);

    auto * index = make_index_2d_taxicab (domain, h, w);

    auto lambda = [](IJ ij) -> ValueType {return ij.i + ij.j;};
    index->map_value<ValueType> (lambda);

    return 0;
}

