//
// Created by Mann on 11.03.2023.
//
#pragma once

#include <cassert>

#include "topology/node.h"
#include "topology/domain.cpp"
#include "topology/summation_node.cpp"

namespace summation_node_test {
    template <class T, T seed_value = T{}>
    void _test_neighbour_sum(const T a_value, const T b_value) {
        const int MAX_NEIGHBORS = 3;

        TopologyNodeDomain d;

        auto *node_a = d.register_id(new SummationTopologyNode<MAX_NEIGHBORS, T, seed_value>{a_value});
        auto *node_b = d.register_id(new SummationTopologyNode<MAX_NEIGHBORS, T, seed_value>{b_value});
        auto *node_c = d.register_id(new TopologyNode<MAX_NEIGHBORS>{});

        node_a->subscribeTo(node_a);
        node_a->subscribeTo(node_b);
        node_a->subscribeTo(node_c);

        int sum = node_a->accumulate_neighbours();
        std::cout << "S = " << sum << "\n";

        assert (sum == a_value + b_value + seed_value);
    }
};