#include <iostream>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <vector>

#include "lib/topology/node.h"
#include "lib/topology/domain.cpp"
#include "lib/topology/summation_node.cpp"

int main()
{
    const int MAX_NEIGHBORS = 2;

    TopologyNodeDomain d;

    auto *node_a = d.register_id(new ValuedTopologyNode<MAX_NEIGHBORS, int>{});
    auto *node_b = d.register_id(new ValuedTopologyNode<MAX_NEIGHBORS, int>{});

    node_a->subscribeTo(node_a);
    node_a->subscribeTo(node_b);

    node_a->printNeighbourIds();

    node_a->unsubscribeFrom(node_a);

    node_a->printNeighbourIds();

    return 0;
}

/*

const int MAX_NEIGHBORS = 2;
void _main(TopologyNodeDomain<TopologyNode<int, MAX_NEIGHBORS>> & nodeDomain) {

    std::cout << "create nodes\n";
    auto node_1 = nodeDomain.newNode();
    auto node_2 = nodeDomain.newNode();
    auto node_3 = nodeDomain.newNode();

    std::cout << "tid = " << typeid(node_1).name() << "\n";
    std::cout << "connect nodes\n";
    node_1->subscribeTo(node_2);
    node_1->subscribeTo(node_3);
    node_1->printNeighbourIds();
    node_1->unsubscribeFrom(node_2);
    node_1->printNeighbourIds();

    std::cout << "end _main\n";
}

int main(){
    std::cout << "create domain\n";
    TopologyNodeDomain <TopologyNode<int, MAX_NEIGHBORS>> nodeDomain;

    std::cout << "enter _main\n";
    _main(nodeDomain);
    std::cout << "exit _main\n";

    auto * sNode1 = new SummationTopologyNode <int, 2>{1};
    delete sNode1;

    return 0;
}*/