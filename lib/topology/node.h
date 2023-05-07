#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
//
// Created by Mann on 20.03.2023.
//

#ifndef CPP__CONWAY_NODE_H
#define CPP__CONWAY_NODE_H

#include <vector>
#include <cassert>
#include <functional>
#include <algorithm>
#include <stdexcept>

namespace topology {


template<typename ValueType>
void neighbor_reduce(std::function<ValueType(ValueType, ValueType)> func, ValueType init_val = ValueType{});


class Node {
    /*
        TODO:
            - [ ] value allocator template
     */

private:

    void *value_ptr_;

    int id_;

protected:
    void set_id(int id) {
        id_ = id;
    }

public:
    std::vector<Node *> neighbors_; // TODO: Write an iterator for neighbors

    // Construction / Destruction --------------------------------------------------------------------------------------

    explicit Node() {
        value_ptr_ = nullptr;
    };

    Node(Node &&node) : Node() {
        value_ptr_ = node.value_ptr_;
        node.value_ptr_ = nullptr;
    }

    Node(Node &node) : Node() {
        value_ptr_ = node.value_ptr_;
        node.value_ptr_ = nullptr;
    }

    Node(void * value_ptr) : Node(){
        set_value_ptr(value_ptr);
    }

    Node operator=(Node &&val) = delete;

    ~Node() = default;

    // Behavioral ------------------------------------------------------------------------------------------------------

    const int id() const {
        return id_;
    }

    void *value_ptr() const {
        return value_ptr_;
    }

    void set_value_ptr(void *ptr) {
        value_ptr_ = ptr;
    }

    // Structural ------------------------------------------------------------------------------------------------------
    void add_neighbor(Node * node) {
        if(has_neighbor(node)) throw std::logic_error("Trying to add already added node " + std::to_string(size_t(node)) + " with id " + std::to_string(node->id()));
        neighbors_.emplace_back(node);
    }

    bool has_neighbor(Node * node) {
        return std::find(neighbors_.begin(), neighbors_.end(), node) != neighbors_.end();
    }

    void remove_neighbor(Node * node) {
        std::remove(neighbors_.begin(), neighbors_.end(), node);
    }

    void remove_all_neighbors() {
        neighbors_.clear();
    }

    // Functional ------------------------------------------------------------------------------------------------------

    template<typename ValueType>
    ValueType neighbor_reduce(const std::function<void(ValueType &, ValueType &)> &func,
                              ValueType init_val = ValueType{}) {
        ValueType result = init_val;
        for (const Node *neighbor: neighbors_) {
            func(result, *static_cast<ValueType *>(neighbor->value_ptr()));
        }
        return result;
    }

    void neighbor_map(const std::function<void(Node*)> &func) {
        for(Node* neighbor: neighbors_) {
            func(neighbor);
        }
    }

};

auto sum = [] (int& accumulated, int& value)-> void  {
    accumulated += value;
};

} // namespace topology

#endif //CPP__CONWAY_NODE_H

#pragma clang diagnostic pop