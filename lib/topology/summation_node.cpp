#pragma once

#include "node.cpp"


template <class ValueType, const int MAX_NEIGHBOURS, const ValueType INITIAL_SUM = 0>
class SummationTopologyNode : public TopologyNode <ValueType, MAX_NEIGHBOURS>{
public:
    explicit SummationTopologyNode(int id, const ValueType initial_sum = INITIAL_SUM)
        : TopologyNode<ValueType, MAX_NEIGHBOURS>::TopologyNode(id),
        _initial_sum{initial_sum},
        _cached_sum{initial_sum} {}

    ~SummationTopologyNode() = default;

    ValueType sumNeighbors(){
        ValueType sum{_initial_sum};
        for (int i = 0; i != TopologyNode <ValueType, MAX_NEIGHBOURS>::_neighborCount; ++ i)
            sum += TopologyNode <ValueType, MAX_NEIGHBOURS>::_neighbors[i];
        setCachedSum(sum);
        return sum;
    }

    ValueType cachedSum() {return _cached_sum;}

protected:
    const ValueType _initial_sum;
    ValueType _cached_sum;

    void setCachedSum(ValueType sum){ _cached_sum = sum;}
};
