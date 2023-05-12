#ifndef CPP__CONWAY_NODE_H
#define CPP__CONWAY_NODE_H

#include <vector>
#include <cassert>
#include <functional>
#include <algorithm>
#include <stdexcept>

namespace topology {


class Node {

private:

    void *value_ptr_;

    void remove_neighbor_(Node * node) {
        auto neighbor_iterator = std::find(neighbors_.begin(), neighbors_.end(), node);
        if (neighbor_iterator == neighbors_.end())
            return;
        neighbors_.erase(neighbor_iterator);
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

    // Value -----------------------------------------------------------------------------------------------------------

    void *value_ptr() const {
        return value_ptr_;
    }

    void set_value_ptr(void *ptr) {
        value_ptr_ = ptr;
    }

    // Structural ------------------------------------------------------------------------------------------------------

    void add_neighbor(Node * node) {
        neighbors_.emplace_back(node);
    }

    bool has_neighbor(Node * node) {
        return std::find(neighbors_.begin(), neighbors_.end(), node) != neighbors_.end();
    }

    void remove_neighbor(Node * node) {
        remove_neighbor_(node);
        node->remove_neighbor_(this);
    }

    void remove_all_neighbors() {
        for(Node* neighbor : neighbors_) {
            remove_neighbor(neighbor);
        }
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

};

// Stuff ---------------------------------------------------------------------------------------------------------------
auto sum = [] (int& accumulated, int& value)-> void  {
    accumulated += value;
};


} // namespace topology

#endif //CPP__CONWAY_NODE_H

//#pragma clang diagnostic pop