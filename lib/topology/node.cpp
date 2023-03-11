#pragma once

#include <iostream>
#include <stdexcept>

#include "node.h"

template <int MAX_NEIGHBOURS_>
class TopologyNode : public AbstractTopologyNode{
public:
    typedef AbstractTopologyNode::ValueType ValueType;
    typedef TopologyNode<MAX_NEIGHBOURS_> NodeType;
    const int MAX_NEIGHBOURS = MAX_NEIGHBOURS_;

    TopologyNode() = default;
    ~TopologyNode() = default;

    decltype(auto) subscribeTo(auto *neighbour);
    decltype(auto) unsubscribeFrom(const auto *neighbor);

    int neighbourCount() {return _neighborCount;}

    void printNeighbourIds();

    [[nodiscard]] virtual const TopologyNodeRole role() const override {return TopologyNodeRole{.has_value=false};}

protected:

    int _neighborCount = 0;
    TopologyNode <MAX_NEIGHBOURS_> * _neighbors [MAX_NEIGHBOURS_];

    int neighbourIndex(const auto *neighbor) const;
    decltype(auto) neighbourAt(const int neighborIndex = 0);
    decltype(auto) unsubscribeByIndex(const int neighborIndex = 0);

};


template <int MAX_NEIGHBOURS_, class ValueType_>
class ValuedTopologyNode : public TopologyNode <MAX_NEIGHBOURS_> {
public:
    typedef ValueType_ ValueType;
    typedef ValuedTopologyNode<MAX_NEIGHBOURS_, ValueType> NodeType;
    const int MAX_NEIGHBOURS = MAX_NEIGHBOURS_;

    ValuedTopologyNode(): TopologyNode<MAX_NEIGHBOURS_>() {setValue(ValueType_{});}
    explicit ValuedTopologyNode(ValueType_ value) : TopologyNode<MAX_NEIGHBOURS_>() { setValue(value);}
    ~ValuedTopologyNode() = default;

    const ValueType& value(){return _value;};
    void setValue(ValueType value){ _value = value;}

    [[nodiscard]] virtual const TopologyNodeRole role() const override {return TopologyNodeRole{.has_value=true};}
protected:
    ValueType _value;


};

// ----------------------------------------------- IMPLEMENTATION -----------------------------------------------------

template <const int MAX_NEIGHBOURS>
int TopologyNode<MAX_NEIGHBOURS>::neighbourIndex(const auto *neighbor) const {
    for(int k = 0; k != _neighborCount; ++ k)
        if (_neighbors[k] == neighbor)
            return k;
    return NOT_A_NEIGHBOR;
}

template <const int MAX_NEIGHBOURS>
decltype(auto) TopologyNode<MAX_NEIGHBOURS>::neighbourAt(const int neighborIndex){
    return _neighbors[neighborIndex];
}

template <const int MAX_NEIGHBOURS>
decltype(auto) TopologyNode<MAX_NEIGHBOURS>::subscribeTo(auto *neighbour){
    if (_neighborCount == MAX_NEIGHBOURS)
        throw std::out_of_range("Attempt to add neighbor exceeds MAX_NEIGHBOURS_ constant");
    _neighbors[_neighborCount] = neighbour;
    _neighborCount ++;
    return this;
}

template <const int MAX_NEIGHBOURS>
decltype(auto) TopologyNode<MAX_NEIGHBOURS>::unsubscribeByIndex(const int neighborIndex){
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

template <const int MAX_NEIGHBOURS>
decltype(auto) TopologyNode<MAX_NEIGHBOURS>::unsubscribeFrom(const auto *neighbor){
    const int neighborIndex = neighbourIndex(neighbor);
    if (neighborIndex == NOT_A_NEIGHBOR)
        throw std::out_of_range("Attempt to removeNeighbor neighbor which is not subscribed");
    unsubscribeByIndex(neighborIndex);
    return this;
}

template <const int MAX_NEIGHBOURS>
void TopologyNode<MAX_NEIGHBOURS>::printNeighbourIds(){
    std::cout << id() << ": {";
    for(int i = 0; i != _neighborCount; ++ i)
        std::cout << neighbourAt(i)->id() << (i + 1 == _neighborCount ? "" : ", " ) ;
    std::cout << "}\n";
}
