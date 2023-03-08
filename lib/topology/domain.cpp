#pragma once

#include "domain.h"

auto * TopologyNodeDomain::register_id(auto* node){
    node->set_id(make_id());
    _nodes.push_back(node);
    return node;
}

auto * TopologyNodeDomain::register_id(auto && node){
    node.set_id(make_id());
    auto node_copy = new decltype(node)(node);
    _nodes.push_back(node_copy);
    return node_copy;
}