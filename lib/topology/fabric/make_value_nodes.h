//
// Created by Mann on 13.03.2023.
//

#ifndef CPP__CONWAY_MAKE_VALUE_NODES_H
#define CPP__CONWAY_MAKE_VALUE_NODES_H

#include "topology/value_node.h"
#include "topology/summation_node.h"
#include "topology/domain.h"

namespace topology {

    template<int MaxNeighbours, class ValueType>
    NodeDomain* make_value_nodes(int number_of_nodes, NodeDomain* domain, ValueType value = ValueType{}) {
        // Why ValueType value and not value& ?! Because if you want 10 nodes with same value make fucking one node!
        // Think networkly, dude!

        for (int n = 0; n != number_of_nodes; ++ n) {
            domain->register_id(ValueNode<MaxNeighbours, ValueType> {value});
        }
        return domain;
    }

    template<int MaxNeighbours, class ValueType, ValueType summation_seed=ValueType{}>
    NodeDomain* make_summation_nodes(int number_of_nodes, NodeDomain* domain, ValueType value = ValueType{}) {
        // Why ValueType value and not value& ?! see make_value_nodes()

        for (int n = 0; n != number_of_nodes; ++ n) {
            domain->register_id(new SummationNode<MaxNeighbours, ValueType, summation_seed> {value});
        }

        return domain;
    }

}

#endif //CPP__CONWAY_MAKE_VALUE_NODES_H
