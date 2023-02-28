#pragma once

#include "node.cpp"


template <class ValueType, const int MAX_NEIGHBOURS, ValueType INITIAL_SUM = 0>
class SummationTopologyNode : public TopologyNode <ValueType, MAX_NEIGHBOURS>{
public:
    explicit SummationTopologyNode(int id, const ValueType initial_sum = INITIAL_SUM) : TopologyNode<ValueType, MAX_NEIGHBOURS>::SummationTopologyNode(id), _initial_sum{initial_sum} {}

    ValueType sumNeighbors(){
        ValueType sum{INITIAL_SUM};
        for (int i = 0; i != TopologyNode <ValueType, MAX_NEIGHBOURS>::_neighborCount; ++ i)
            sum += TopologyNode <ValueType, MAX_NEIGHBOURS>::_neighbors[i];
        return sum;
    }
protected:
    const ValueType _initial_sum;
};
