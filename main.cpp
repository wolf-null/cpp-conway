#include <iostream>


#include <cassert>
#include <exception>
#include <stdexcept>
#include <vector>



/*
template <class ValueType, const int MAX_NEIGHBOURS>
class MapReduceTopologyNode : public TopologyNode <ValueType, MAX_NEIGHBOURS>
{
public:
    ValueType reduceNeighbors() override {
        ValueType accumulated = _reduceNeighborValuesInit();
        for (int k = 0; k != TopologyNode<ValueType, MAX_NEIGHBOURS>::_neighborCount; ++ k)
            accumulated = _reduceNeighborValues(accumulated, TopologyNode<ValueType, MAX_NEIGHBOURS>::_neighbors[k]);
        return accumulated;
    }

protected:
    virtual ValueType _reduceNeighborValues(const ValueType value1, const ValueType value2) const = 0;
    virtual inline const ValueType _reduceNeighborValuesInit() const = 0;
};

template <const int MAX_NEIGHBOURS>
class IntMapReduceTopologyNode : public MapReduceTopologyNode <int, MAX_NEIGHBOURS>
{
private:
    int _reduceNeighborValues(const int value1, const int value2) const override {
        return value1 + value2;
    };

    inline const int _reduceNeighborValuesInit() const override {
        return 0;
    };
};

*/

#include "lib/topology/node.cpp"
#include "lib/topology/domain.cpp"

const int MAX_NEIGHBORS = 2;

void _main(TopologyNodeDomain<TopologyNode<int, MAX_NEIGHBORS>> & nodeDomain) {
    std::cout << "create nodes\n";
    auto node_1 = nodeDomain.newNode();
    auto node_2 = nodeDomain.newNode();
    auto node_3 = nodeDomain.newNode();

    std::cout << "connect nodes\n";
    node_1->addNeighbour(node_2);
    node_1->addNeighbour(node_3);
    node_1->printNeighbourIds();
    node_1->removeNeighbour(node_2);
    node_1->printNeighbourIds();
    node_1->popNeighbour(0);
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