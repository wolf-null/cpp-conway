#pragma once

#include "node.cpp"
#include <vector>

template < TopologyNodeConcept TopologyNodeType>
class TopologyNodeDomain
{
public:
    typedef TopologyNodeType NODE_TYPE;

    TopologyNodeDomain() {_last_id = 1;};
    ~TopologyNodeDomain() ;

    TopologyNodeType * newNode();
private:
    int _last_id;
    std::vector <TopologyNodeType*> created_nodes;
};

template <TopologyNodeConcept TopologyNodeType>
TopologyNodeDomain<TopologyNodeType>::~TopologyNodeDomain() {
    for (auto * node : created_nodes)
        delete node;
}

// ----------------------------------------------- IMPLEMENTATION -----------------------------------------------------

template <TopologyNodeConcept TopologyNodeType>
TopologyNodeType * TopologyNodeDomain<TopologyNodeType>::newNode(){
    auto * node = new TopologyNodeType {_last_id};
    created_nodes.push_back(node);
    _last_id += 1;
    return node;
}
