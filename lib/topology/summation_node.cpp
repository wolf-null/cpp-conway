#pragma once


#include "node.cpp"

template <class T> concept SummableType = requires(T a, T b) {
    {a + b} -> std::convertible_to<T>;
    std::is_copy_constructible<T>::value;
    std::is_default_constructible<T>::value;
};

template <int MAX_NEIGHBOURS_, SummableType ValueType_, ValueType_ summation_seed=ValueType_{}>
class SummationTopologyNode : public ValuedTopologyNode <MAX_NEIGHBOURS_, ValueType_> {
public:
    typedef ValueType_ ValueType;
    typedef ValuedTopologyNode<MAX_NEIGHBOURS_, ValueType> NodeType;
    const int MAX_NEIGHBOURS = MAX_NEIGHBOURS_;

    explicit SummationTopologyNode(ValueType value = ValueType{}) : ValuedTopologyNode<MAX_NEIGHBOURS_, ValueType_>(value){};
    ~SummationTopologyNode() = default;

    ValueType accumulate_neighbours();

    [[nodiscard]] virtual const TopologyNodeRole role() const override {return TopologyNodeRole{.has_value=true};}

protected:
    using ValuedTopologyNode<MAX_NEIGHBOURS_, ValueType>::_neighborCount;
    using ValuedTopologyNode<MAX_NEIGHBOURS_, ValueType>::_neighbors;
    using ValuedTopologyNode<MAX_NEIGHBOURS_, ValueType>::value;

};

template <int MAX_NEIGHBOURS_, SummableType ValueType_, ValueType_ summation_seed>
ValueType_ SummationTopologyNode<MAX_NEIGHBOURS_, ValueType_, summation_seed>::accumulate_neighbours(){
    ValueType sum {summation_seed};

    if (_neighborCount == 0)
        return sum;


    for (int idx = 0; idx != _neighborCount; ++ idx) {
        if (!_neighbors[idx]->role().has_value)
            continue;
        auto val = static_cast<ValuedTopologyNode<MAX_NEIGHBOURS_, ValueType_>*> (_neighbors[idx])->value();
        sum += static_cast<ValuedTopologyNode<MAX_NEIGHBOURS_, ValueType_>*> (_neighbors[idx])->value();
    }
    return sum;
}
