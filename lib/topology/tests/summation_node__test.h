#ifndef CPP__CONWAY_SUMMATION_NODE__TEST_H
#define CPP__CONWAY_SUMMATION_NODE__TEST_H

#include <cassert>

#include "topology/node.h"
#include "topology/domain.h"
#include "topology/value_node.h"
#include "topology/summation_node.h"

namespace topology_tests {

    template <class T, T SeedValue = T{}>
    void _test_neighbour_sum(const T a_value, const T b_value) {
        using namespace topology;

        const int MAX_NEIGHBORS = 3;

        NodeDomain d;

        auto *node_a = d.register_id(new SummationNode<MAX_NEIGHBORS, T, SeedValue>{a_value});
        auto *node_b = d.register_id(new SummationNode<MAX_NEIGHBORS, T, SeedValue>{b_value});
        auto *node_c = d.register_id(new Node<MAX_NEIGHBORS>{});

        node_a->subscribe_to(node_a);
        node_a->subscribe_to(node_b);
        node_a->subscribe_to(node_c);

        int sum = node_a->accumulate_neighbours();
        std::cout << "S = " << sum << "\n";

        assert (sum == a_value + b_value + SeedValue);
    }
}

#endif //CPP__CONWAY_SUMMATION_NODE__TEST_H
