#include <iostream>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <vector>

#include "lib/topology/node.cpp"
#include "lib/topology/domain.cpp"

const int MAX_NEIGHBORS = 2;

void _main(TopologyNodeDomain<TopologyNode<int, MAX_NEIGHBORS>> & nodeDomain) {
    std::cout << "create nodes\n";
    auto node_1 = nodeDomain.newNode();
    auto node_2 = nodeDomain.newNode();
    auto node_3 = nodeDomain.newNode();

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
    return 0;
}