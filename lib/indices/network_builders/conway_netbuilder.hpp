#pragma once
#include <stdexcept>
#include <iostream>

#include "indices/index_model.hpp"
#include "indices/neighborhood_model.hpp"
#include "indices/ij.hpp"

class ConwayNetworkBuilder {
private:
    IndexModel * index_model_ = nullptr;
    NeighborhoodModel * neighborhood_model_ = nullptr;

public:

    ConwayNetworkBuilder(
            IndexModel * index_model,
            NeighborhoodModel * neighborhood_model
            ) :
        index_model_ {index_model},
        neighborhood_model_{neighborhood_model}
    {}

    void build_neighborhood() {
        auto connect_neighbors = [this] (IJ coord) -> void {
            if (coord.state.get() == IJState::PADDING)
                return;
            if (coord.state.get() == IJState::INVALID)
                throw;
            topology::Node * node = index_model_->get_node(coord);
            std::vector <IJ> neighbors = neighborhood_model_->neighbor_indices_of(coord);
            for (auto neighbor_coord : neighbors) {
                auto * neighbor_node = index_model_->get_node(neighbor_coord);
                node->add_neighbor(neighbor_node);
            }
        };
        index_model_->map_IJ(connect_neighbors);
    }

};
