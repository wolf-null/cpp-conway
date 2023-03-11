//
// Created by Mann on 11.03.2023.
//
#pragma once

#include <cassert>

#include "topology/node.h"
#include "topology/domain.cpp"
#include "topology/summation_node.cpp"

namespace summation_node_test {
    template <class T, T SeedValue = T{}>
    void _test_neighbour_sum(const T a_value, const T b_value) {
        const int MAX_NEIGHBORS = 3;

        TopologyNodeDomain d;

        auto *node_a = d.register_id(new SummationTopologyNode<MAX_NEIGHBORS, T, SeedValue>{a_value});
        auto *node_b = d.register_id(new SummationTopologyNode<MAX_NEIGHBORS, T, SeedValue>{b_value});
        auto *node_c = d.register_id(new Node<MAX_NEIGHBORS>{});

        node_a->subscribe_to(node_a);
        node_a->subscribe_to(node_b);
        node_a->subscribe_to(node_c);

        int sum = node_a->accumulate_neighbours();
        std::cout << "S = " << sum << "\n";

        assert (sum == a_value + b_value + SeedValue);
    }
}