//
// Created by Mann on 21.03.2023.
//

#ifndef CPP__CONWAY_DOMAIN_H
#define CPP__CONWAY_DOMAIN_H

#include <list>
#include <functional>

#include "node.h"

class Domain {
private:
    std::list<Node> nodes_;

    int last_id_;

    [[nodiscard]] int next_id() {return last_id_++;}

public:
    Domain() : last_id_{1} {};

    int register_node(Node * node) {
        int new_node_id = next_id();
        node->set_id(new_node_id);
        nodes_.push_back(std::forward<Node&&>(*node));
        return new_node_id;
    }

    int register_node(Node && node) {
        int new_node_id = next_id();
        node.set_id(new_node_id);
        nodes_.push_back(std::forward<Node&&>(node));
        return new_node_id;
    }

    Node* make_node() {
        register_node(std::forward<Node>(Node{}));
        return &nodes_.back();
    }

    template <typename ValueType>
    Node* make_node(ValueType && val) {
        Node * node = make_node();
        node->set_value_ptr(static_cast<void*> (new ValueType{std::forward<ValueType>(val)}));
        return node;
    }

    template<typename ValueType>
    Node* make_node(std::function<ValueType()> *generator) {
        return make_node(generator());
    }

    template<typename ValueType>
    std::function<Node*()> node_maker(std::function<ValueType()> *generator) {
        return [generator, this] () -> Node* {return make_node(generator);};
    }

    int size() {return nodes_.size();}




};

#endif //CPP__CONWAY_DOMAIN_H
