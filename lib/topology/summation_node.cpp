#pragma once

#include "node.cpp"

template <class T> concept SummableType = requires(T a, T b) {
    {a + b} -> std::convertible_to<T>;
    std::is_copy_constructible<T>::value;
    std::is_default_constructible<T>::value;
};

template <int MAX_NEIGHBOURS, SummableType ValueType, ValueType summation_seed=ValueType{}>
class SummationTopologyNode : public ValuedTopologyNode <MAX_NEIGHBOURS, ValueType> {
public:
    explicit SummationTopologyNode(ValueType value = ValueType{}) : ValuedTopologyNode<MAX_NEIGHBOURS, ValueType>(value){};
    ~SummationTopologyNode() = default;

    ValueType accumulate_neighbours();

    [[nodiscard]] virtual const TopologyNodeRole role() const override {return TopologyNodeRole{.has_value=true};}

protected:
    using ValuedTopologyNode<MAX_NEIGHBOURS, ValueType>::_neighborCount;
    using ValuedTopologyNode<MAX_NEIGHBOURS, ValueType>::_neighbors;
    using ValuedTopologyNode<MAX_NEIGHBOURS, ValueType>::value;

};

template <int MAX_NEIGHBOURS, SummableType ValueType, ValueType summation_seed>
ValueType SummationTopologyNode<MAX_NEIGHBOURS, ValueType, summation_seed>::accumulate_neighbours(){
    ValueType sum {summation_seed};

    if (_neighborCount == 0)
        return sum;

    for (int idx = 0; idx != _neighborCount; ++ idx) {
        if (!_neighbors[idx]->role().has_value)
            continue;

        sum += static_cast<ValuedTopologyNode<MAX_NEIGHBOURS, ValueType>*> (_neighbors[idx])->value();
    }
    return sum;
}
