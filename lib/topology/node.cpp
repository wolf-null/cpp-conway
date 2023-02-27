#pragma once

#include <iostream>
#include <stdexcept>

template <class ValueType, const int MAX_NEIGHBOURS>
class TopologyNode {
public:
    const int NOT_A_NEIGHBOR = -1;

    TopologyNode(const int id) : _id{id} {
        std::cout << "[" << _id << "]\tconstructor\n";
    };

    ~TopologyNode() {
        std::cout << "[" << _id << "]\tdestructor\n";
    }

    // values -------------------------------------------------------------------------------------------------------

    auto getValue(){return _value;};
    void setValue(ValueType && value){_value = value;}

    int getNeighborIndex(const auto *neighbor) const {
        for(int k = 0; k != _neighborCount; ++ k)
            if (_neighbors[k] == neighbor)
                return k;
        return NOT_A_NEIGHBOR;
    }

    auto getNeighborAt(const int neighborIndex = 0){
        return _neighbors[neighborIndex];
    }

    // subscription -------------------------------------------------------------------------------------------------

    auto addNeighbour(auto *neighbour){
        if (_neighborCount == MAX_NEIGHBOURS)
            throw std::out_of_range("Attempt to add neighbor exceeds MAX_NEIGHBOURS constant");
        _neighbors[_neighborCount] = neighbour;
        _neighborCount ++;
        return this;
    }

    auto popNeighbour(const int neighborIndex = 0){
        if (neighborIndex == NOT_A_NEIGHBOR)
            throw std::out_of_range("Attempt to delete NOT_A_NEIGHBOUR");

        if (neighborIndex < 0)
            throw std::out_of_range("Attempt to popNeighbour index < 0");

        if (neighborIndex >= _neighborCount)
            throw std::out_of_range("Attempt to removeNeighbor index exceeding neighbor count");

        auto deletedNeighbour = getNeighborAt(neighborIndex);

        for(int k = neighborIndex; k < _neighborCount - 1; ++ k)
            _neighbors[k] = _neighbors[k + 1];
        -- _neighborCount;

        return deletedNeighbour;
    }

    auto removeNeighbour(const auto *neighbor){
        const int neighborIndex = getNeighborIndex(neighbor);
        if (neighborIndex == NOT_A_NEIGHBOR)
            throw std::out_of_range("Attempt to removeNeighbor neighbor which is not subscribed");
        popNeighbour(neighborIndex);
        return this;
    }

    const int id(){
        return _id;
    }

    void printNeighbourIds(){
        std::cout << _id << ": {";
        for(int i = 0; i != _neighborCount; ++ i)
            std::cout << getNeighborAt(i)->id() << (i + 1 == _neighborCount ? "" : ", " ) ;
        std::cout << "}\n";
    }

protected:

    ValueType *_value;
    const int _id;
    int _neighborCount = 0;
    TopologyNode <ValueType, MAX_NEIGHBOURS> * _neighbors [MAX_NEIGHBOURS];

};