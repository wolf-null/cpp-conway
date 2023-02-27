#pragma once

#include "node.cpp"
#include <vector>

template <class TopologyNodeType>
class TopologyNodeDomain
{
public:
    TopologyNodeDomain() {_last_id = 1;};
    ~TopologyNodeDomain() {
        std::cout << "domain destructor begin\n";
        for (auto * node : created_nodes){
            delete node;
        }
        std::cout << "domain destructor end\n";
    }

    TopologyNodeType * newNode(){
        auto * node = new TopologyNodeType {_last_id};
        created_nodes.push_back(node);
        _last_id += 1;
        return node;
    }
private:
    int _last_id;
    std::vector <TopologyNodeType*> created_nodes;
};

