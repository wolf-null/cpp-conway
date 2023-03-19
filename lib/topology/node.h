#ifndef CPP__CONWAY_NODE_H
#define CPP__CONWAY_NODE_H

#include <stdexcept>
#include <array>
#include <iostream>

#include "abstract_node.h"

namespace topology {

    template<int MaxNeighbours>
    class Node : public AbstractNode {
    public:
        struct NodeRole : public AbstractNodeRole{
            NodeRole() = default;
            bool has_value;
            static constexpr int max_neighbours = MaxNeighbours;
        };
        virtual AbstractNodeRole* role() const override {
            return static_cast <AbstractNodeRole*> (new NodeRole{.has_value=false});
        }

        static constexpr int max_neighbours{MaxNeighbours};

        Node() = default;
        ~Node() = default;

        decltype(auto) subscribe_to(auto *neighbour);
        decltype(auto) unsubscribe_from(const auto *neighbor);

        int neighbour_count() { return neighbour_count_; }

        void print_neighbour_ids();

    protected:
        int neighbour_count_{0};
        std::array<Node<max_neighbours> *, max_neighbours> neighbors_;

        int neighbour_index(const auto *neighbor) const;
        decltype(auto) neighbour_at(const int neighborIndex = 0);
        decltype(auto) unsubscribe_by_index(const int neighborIndex = 0);
    };

// ----------------------------------------------- IMPLEMENTATION -----------------------------------------------------

    template<const int MaxNeighbours>
    int Node<MaxNeighbours>::neighbour_index(const auto *neighbor) const {
        for (int k = 0; k != neighbour_count_; ++k)
            if (neighbors_[k] == neighbor)
                return k;
        return NOT_A_NEIGHBOR;
    }

    template<const int MaxNeighbours>
    decltype(auto) Node<MaxNeighbours>::neighbour_at(const int neighborIndex) {
        return neighbors_[neighborIndex];
    }

    template<const int MaxNeighbours>
    decltype(auto) Node<MaxNeighbours>::subscribe_to(auto *neighbour) {
        if (neighbour_count_ == max_neighbours)
            throw std::out_of_range("Attempt to add neighbor exceeds MAX_NEIGHBOURS_ constant");
        neighbors_[neighbour_count_] = neighbour;
        neighbour_count_++;
        return this;
    }

    template<const int MaxNeighbours>
    decltype(auto) Node<MaxNeighbours>::unsubscribe_by_index(const int neighborIndex) {
        if (neighborIndex == NOT_A_NEIGHBOR)
            throw std::out_of_range("Attempt to delete NOT_A_NEIGHBOUR");

        if (neighborIndex < 0)
            throw std::out_of_range("Attempt to unsubscribe_by_index index < 0");

        if (neighborIndex >= neighbour_count_)
            throw std::out_of_range("Attempt to removeNeighbor index exceeding neighbor count");

        auto deletedNeighbour = neighbour_at(neighborIndex);

        for (int k = neighborIndex; k < neighbour_count_ - 1; ++k)
            neighbors_[k] = neighbors_[k + 1];
        --neighbour_count_;

        return deletedNeighbour;
    }

    template<const int MaxNeighbours>
    decltype(auto) Node<MaxNeighbours>::unsubscribe_from(const auto *neighbor) {
        const int neighborIndex = neighbour_index(neighbor);
        if (neighborIndex == NOT_A_NEIGHBOR)
            throw std::out_of_range("Attempt to removeNeighbor neighbor which is not subscribed");
        unsubscribe_by_index(neighborIndex);
        return this;
    }

    template<const int MaxNeighbours>
    void Node<MaxNeighbours>::print_neighbour_ids() {
        std::cout << id() << ": {";
        for (int i = 0; i != neighbour_count_; ++i)
            std::cout << neighbour_at(i)->id() << (i + 1 == neighbour_count_ ? "" : ", ");
        std::cout << "}\n";
    }
}
#endif //CPP__CONWAY_NODE_H
