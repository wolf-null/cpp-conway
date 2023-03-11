#ifndef CPP__KONWAY_DOMAIN_H
#define CPP__KONWAY_DOMAIN_H

#include <vector>

#include "node.h"

class TopologyNodeDomain
{
public:
    TopologyNodeDomain() {_last_id = 1;};
    ~TopologyNodeDomain() {
        for (auto * node : _nodes)
            delete node;
    }

    auto* register_id(auto* node);
    auto * register_id(auto && node);
    auto iterate_nodes() {
        return _nodes.begin();
    }
private:
    int _last_id;
    [[nodiscard]] const int make_id(){return _last_id++;}
    std::vector <AbstractNode*> _nodes;
};

#endif //CPP__KONWAY_DOMAIN_H
