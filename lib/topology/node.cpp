#pragma once

#include <iostream>
#include <stdexcept>
#include <array>

#include "node.h"

template <int C_MAX_NEIGHBOURS>
class TopologyNode : public AbstractTopologyNode {
public:
    static constexpr int MAX_NEIGHBOURS = C_MAX_NEIGHBOURS;

    TopologyNode() = default;
    ~TopologyNode() = default;

    decltype(auto) subscribeTo(auto *neighbour);
    decltype(auto) unsubscribeFrom(const auto *neighbor);

    int neighbourCount() {return _neighborCount;}

    void printNeighbourIds();

    [[nodiscard]] virtual const TopologyNodeRole role() const override {return TopologyNodeRole{.has_value=false};}

protected:
    int _neighborCount = 0;

    std::array <TopologyNode<MAX_NEIGHBOURS>*, MAX_NEIGHBOURS> _neighbors;

    int neighbourIndex(const auto *neighbor) const;
    decltype(auto) neighbourAt(const int neighborIndex = 0);
    decltype(auto) unsubscribeByIndex(const int neighborIndex = 0);
};

template <int MAX_NEIGHBOURS, class ValueType>
class ValuedTopologyNode : public TopologyNode <MAX_NEIGHBOURS> {
public:
    ValuedTopologyNode(): TopologyNode<MAX_NEIGHBOURS>() {setValue(ValueType{});}
    explicit ValuedTopologyNode(ValueType value) : TopologyNode<MAX_NEIGHBOURS>() { setValue(value);}
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
