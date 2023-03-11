
#ifndef CPP__CONWAY_SUMMATION_NODE_H
#define CPP__CONWAY_SUMMATION_NODE_H

#include "node.h"
#include "value_node.h"

namespace topology {

    template<class T> concept SummableType = requires(T a, T b) {
        { a + b } -> std::convertible_to<T>;
        std::is_copy_constructible<T>::value;
        std::is_default_constructible<T>::value;
    };


    template<int MaxNeighbours, SummableType ValueType, ValueType summation_seed = ValueType{}>
    class SummationNode : public ValueNode<MaxNeighbours, ValueType> {
    public:
        explicit SummationNode(ValueType value = ValueType{}) : ValueNode<MaxNeighbours, ValueType>(value) {};

        ~SummationNode() = default;

        ValueType accumulate_neighbours();

        [[nodiscard]] virtual const NodeRole role() const override { return NodeRole{.has_value=true}; }

    protected:
        using ValueNode<MaxNeighbours, ValueType>::neighbour_count_;
        using ValueNode<MaxNeighbours, ValueType>::neighbors_;
        using ValueNode<MaxNeighbours, ValueType>::value;

    };

    template<int MaxNeighbours, SummableType ValueType, ValueType summation_seed>
    ValueType SummationNode<MaxNeighbours, ValueType, summation_seed>::accumulate_neighbours() {
        ValueType sum{summation_seed};

        if (neighbour_count_ == 0)
            return sum;

        for (int idx = 0; idx != neighbour_count_; ++idx) {
            if (!neighbors_[idx]->role().has_value)
                continue;

            sum += static_cast<ValueNode<MaxNeighbours, ValueType> *> (neighbors_[idx])->value();
        }
        return sum;
    }

}

#endif //CPP__CONWAY_SUMMATION_NODE_H
