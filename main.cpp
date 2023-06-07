#include <iostream>
#include <map>
#include <set>

#include "indices/index_models/taxicab_with_padding.h"
#include "indices/network_builders/conway_netbuilder.hpp"
#include "indices/neighborhood_models/conway_neighbors.hpp"
#include "topology/node.hpp"


int main(int argc, char* argv[]) {
    TaxicabWithPaddingIndexModel index_model;
    index_model.set_shape(IJ{2, 3});

    topology::Node padding_node;
    index_model.set_padding_node(&padding_node);

    topology::Node new_node;
    index_model.assign_nodes <topology::Node> (false);

    ConwayNeighborhoodModel neighborhood_model {};

    ConwayNetworkBuilder builder {
        &index_model,
        &neighborhood_model
    };

    builder.build_neighborhood();

    std::cout << index_model.neighborhood_to_str();

    return 0;
}
