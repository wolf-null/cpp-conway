

#include <iostream>
#include <vector>

#include "indices/index_models/taxicab_padding.h"
#include "topology/node.h"

int main(int argc, char* argv[]) {
    TaxicabWithPaddingIndexModel model;
    model.set_shape(IJ{1, 1});

    topology::Node padding_node;
    model.set_padding_node(&padding_node);

    topology::Node new_node;
    model.set_node(&new_node, IJ{0, 0});

    return 0;
}
