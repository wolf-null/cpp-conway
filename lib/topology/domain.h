#ifndef CPP__CONWAY_DOMAIN_H
#define CPP__CONWAY_DOMAIN_H

#include <vector>
#include <iterator>

#include "node.h"

namespace topology {

class NodeDomain {
public:
    NodeDomain() { last_id_ = 1; };
    ~NodeDomain() {
        for (auto *node: nodes_)
            delete node;
    }

    struct iterator : public std::vector<AbstractNode*>::iterator {};

    iterator begin() {
        auto iter = nodes_.begin();
        return *reinterpret_cast<iterator*> (&iter);
    }
    iterator end() {
        auto iter = nodes_.end();
        return *reinterpret_cast<iterator*> (&iter);
    }

    int length() const {
        return nodes_.size();
    }

    auto *register_id(auto *node);
    //auto *register_id(auto &&node);

    auto iterate_nodes() {
        return nodes_.begin();
    }



private:
    std::vector<AbstractNode *> nodes_;
    int last_id_;

    [[nodiscard]] const int make_id() { return last_id_++; }

};

auto *NodeDomain::register_id(auto *node) {
    node->set_id(make_id());
    nodes_.push_back(node);
    return node;
}
/*
auto *NodeDomain::register_id(auto &&node) {
    node.set_id(make_id());
    auto node_copy = new decltype(&node)(node);
    nodes_.push_back(node_copy);
    return node_copy;
}*/

} //end namespace topology

#endif //CPP__CONWAY_DOMAIN_H

