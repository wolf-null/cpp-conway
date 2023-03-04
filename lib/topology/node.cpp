#pragma once

#include <iostream>
#include <stdexcept>

template <class ValueType, const int maxNeighbours>
class TopologyNode {
public:
    const int NOT_A_NEIGHBOR = -1;

    typedef ValueType VALUE_TYPE;
    const int MAX_NEIGHBOURS = maxNeighbours;

    explicit TopologyNode(const int id) : _id{id} {}
    ~TopologyNode() = default;

    const ValueType& value(){return &_value;};
    void setValue(ValueType & value){_value = value;}

    auto subscribeTo(auto *neighbour);
    auto unsubscribeFrom(const auto *neighbor);

    int id(){return _id;}
    int neighbourCount() {return _neighborCount;}

    void printNeighbourIds();

protected:
    const int _id;
    ValueType _value;

    int _neighborCount = 0;
    TopologyNode <ValueType, maxNeighbours> * _neighbors [maxNeighbours];

    int neighbourIndex(const auto *neighbor) const;
    auto neighbourAt(const int neighborIndex = 0);
    auto unsubscribeByIndex(const int neighborIndex = 0);

};

template <class ValueType, const int MAX_NEIGHBOURS>
int TopologyNode<ValueType, MAX_NEIGHBOURS>::neighbourIndex(const auto *neighbor) const {
    for(int k = 0; k != _neighborCount; ++ k)
        if (_neighbors[k] == neighbor)
            return k;
    return NOT_A_NEIGHBOR;
}

template <class ValueType, const int MAX_NEIGHBOURS>
auto TopologyNode<ValueType, MAX_NEIGHBOURS>::neighbourAt(const int neighborIndex){
    return _neighbors[neighborIndex];
}

template <class ValueType, const int MAX_NEIGHBOURS>
auto TopologyNode<ValueType, MAX_NEIGHBOURS>::subscribeTo(auto *neighbour){
    if (_neighborCount == MAX_NEIGHBOURS)
        throw std::out_of_range("Attempt to add neighbor exceeds maxNeighbours constant");
    _neighbors[_neighborCount] = neighbour;
    _neighborCount ++;
    return this;
}

template <class ValueType, const int MAX_NEIGHBOURS>
auto TopologyNode<ValueType, MAX_NEIGHBOURS>::unsubscribeByIndex(const int neighborIndex){
    if (neighborIndex == NOT_A_NEIGHBOR)
        throw std::out_of_range("Attempt to delete NOT_A_NEIGHBOUR");

    if (neighborIndex < 0)
        throw std::out_of_range("Attempt to unsubscribeByIndex index < 0");

    if (neighborIndex >= _neighborCount)
        throw std::out_of_range("Attempt to removeNeighbor index exceeding neighbor count");

    auto deletedNeighbour = neighbourAt(neighborIndex);

    for(int k = neighborIndex; k < _neighborCount - 1; ++ k)
        _neighbors[k] = _neighbors[k + 1];
    -- _neighborCount;

    return deletedNeighbour;
}

template <class ValueType, const int MAX_NEIGHBOURS>
auto TopologyNode<ValueType, MAX_NEIGHBOURS>::unsubscribeFrom(const auto *neighbor){
    const int neighborIndex = neighbourIndex(neighbor);
    if (neighborIndex == NOT_A_NEIGHBOR)
        throw std::out_of_range("Attempt to removeNeighbor neighbor which is not subscribed");
    unsubscribeByIndex(neighborIndex);
    return this;
}

template <class ValueType, const int MAX_NEIGHBOURS>
void TopologyNode<ValueType, MAX_NEIGHBOURS>::printNeighbourIds(){
    std::cout << _id << ": {";
    for(int i = 0; i != _neighborCount; ++ i)
        std::cout << neighbourAt(i)->id() << (i + 1 == _neighborCount ? "" : ", " ) ;
    std::cout << "}\n";
}
