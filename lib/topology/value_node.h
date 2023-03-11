#ifndef CPP__CONWAY_VALUE_NODE_H
#define CPP__CONWAY_VALUE_NODE_H


#include "node.h"

namespace topology {

    template<int MaxNeighbours, class ValueType>
    class ValueNode : public Node<MaxNeighbours> {
    public:
        ValueNode() : Node<MaxNeighbours>() { set_value(ValueType{}); }
        explicit ValueNode(ValueType value) : Node<MaxNeighbours>() { set_value(value); }
        ~ValueNode() = default;

        const ValueType &value() { return value_; };
        void set_value(ValueType value) { value_ = value; }

        [[nodiscard]] virtual const NodeRole role() const override { return NodeRole{.has_value=true}; }

    protected:
        ValueType value_;

    };
}

#endif //CPP__CONWAY_VALUE_NODE_H
