#ifndef CPP__CONWAY_DOMAIN_H
#define CPP__CONWAY_DOMAIN_H

#include <vector>

#include "node.h"

namespace topology {

    class NodeDomain {
    public:
        NodeDomain() { _last_id = 1; };
        ~NodeDomain() {
            for (auto *node: _nodes)
                delete node;
        }

        auto *register_id(auto *node);
        auto *register_id(auto &&node);

        auto iterate_nodes() {
            return _nodes.begin();
        }

    private:
        std::vector<AbstractNode *> _nodes;
        int _last_id;

        [[nodiscard]] const int make_id() { return _last_id++; }

    };

    auto *NodeDomain::register_id(auto *node) {
        node->set_id(make_id());
        _nodes.push_back(node);
        return node;
    }

    auto *NodeDomain::register_id(auto &&node) {
        node.set_id(make_id());
        auto node_copy = new decltype(node)(node);
        _nodes.push_back(node_copy);
        return node_copy;
    }

}

#endif //CPP__CONWAY_DOMAIN_H

