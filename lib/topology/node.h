//
// Created by Mann on 20.03.2023.
//

#ifndef CPP__CONWAY_NODE_H
#define CPP__CONWAY_NODE_H

#include <vector>
#include <cassert>
#include <functional>

template <typename ValueType>
void neighbor_reduce(std::function<ValueType(ValueType, ValueType)> func, ValueType init_val=ValueType{});

enum ValueTypeID {
    UNDEFINED = 0,
    INT = 1
};

struct ValueDescription {
    ValueTypeID type_id;
};

struct NodeState {

    bool can_evaluate;
};

class Node {
    /*
     Core Node ideas:
        - A node has neighbour nodes
        - A node has a pointer to its value (without specifying value type).
                - This "value" is an external entity, can be only assigned to a node.
        - Since there is a different kind of nodes (inheritors), a node have a field to denote which type of node it is
                - The more general approach is to use non-constant node "roles"
                        + Create NodeRole class
        - Since value is not controlled by a Node and represented via pointer (void*) there should be a description of
                type of the value. The best would be a type, but there is no way to pass types as arguments which
                is usable in operations like static_cast, this is why conversion of the void* value is up to user,
                but this value_helper might be useful.
     */

private:

    ValueDescription value_description_;

    void * value_ptr_;

    NodeState state_;

    int id_;



protected:
    friend class Domain;
    void set_id(int id) {id_ = id;}

public:
    static int last_auto_id;
    int auto_id;

    explicit Node() {
        auto_id = last_auto_id;
        last_auto_id ++;
    };

    Node(Node&& node) : Node() {
        value_ptr_ = node.value_ptr_;
        node.value_ptr_ = nullptr;
    }

    Node(Node& node) : Node() {
        value_ptr_ = node.value_ptr_;
        node.value_ptr_ = nullptr;
    }

    Node operator = (Node && val) = delete;

    ~Node() {};

    int id() {return id_;}

    std::vector <Node*> neighbors_; // TODO: Write an iterator for neighbors

    ValueDescription value_description(ValueDescription d){return value_description_;}
    void set_value_description(ValueDescription d){value_description_ = d;}

    void* value_ptr() const {return value_ptr_;}
    void set_value_ptr(void * ptr) {
        value_ptr_ = ptr;
    }
    void set_value_ptr(void * ptr, ValueDescription d) {value_ptr_ = ptr; set_value_description(d);}

    const NodeState& state() const {return state_;}
    void set_state(NodeState state) {state_ = state;}

    template <typename ValueType>
    ValueType neighbor_reduce(const std::function<ValueType(ValueType, ValueType)>& func, ValueType init_val=ValueType{}) {
        ValueType result = init_val;
        for (const Node * neighbor : neighbors_) {
            result = func(result, *static_cast<ValueType*>(neighbor->value_ptr()));
        }
        return result;
    }

    template <typename ValueType>
    ValueType& neighbor_reduce(const std::function<ValueType&(ValueType&, ValueType&)>& func, ValueType &init_val=ValueType{}) {
        ValueType & result = init_val;
        for (const Node * neighbor : neighbors_) {
            result = func(result, *static_cast<ValueType*>(neighbor->value_ptr()));
        }
        return result;
    }

    template <typename ValueType>
    ValueType& neighbor_reduce(const std::function<ValueType&(ValueType&, ValueType&)>& func, const std::function<bool(ValueType&)> &filter, ValueType &init_val=ValueType{}) {
        ValueType & result = init_val;
        for (const Node * neighbor : neighbors_) {
            if (!filter(*static_cast<ValueType*>(neighbor->value_ptr())))
                continue;
            result = func(result, *static_cast<ValueType*>(neighbor->value_ptr()));
        }
        return result;
    }

    template <typename ValueType>
    static ValueType& node_reduce(std::vector<Node*> &&nodes, const std::function<ValueType&(ValueType&, ValueType&)>& func, ValueType &&init_val=ValueType{}) {
        ValueType & result = init_val;
        for (const Node * neighbor : nodes) {
            result = func(result, *static_cast<ValueType*>(neighbor->value_ptr()));
        }
        return result;
    }

};

int Node::last_auto_id = 0;

#endif //CPP__CONWAY_NODE_H
