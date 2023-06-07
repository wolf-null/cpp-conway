#include "taxicab_with_padding.h"

const IJ TaxicabWithPaddingIndexModel::PADDING_COORD {0, 0, IJState::PADDING};

// --- Indexing ---------------

inline bool TaxicabWithPaddingIndexModel::is_outside(IJ coord) const {
    if (coord.i.get() < 0 || coord.i.get() >= get_shape().i.get())
        return true;

    if (coord.j.get() < 0 || coord.j.get() >= get_shape().j.get())
        return true;

    return false;
}

Index TaxicabWithPaddingIndexModel::index_of(IJ coord) const  {
    if (coord.state.get() == IJState::PADDING)
        return PADDING_INDEX;

    if (is_outside(coord))
        return PADDING_INDEX;

    return CELL_INDEX_ORIGIN + coord.i.get() * get_shape().j.get() + coord.j.get();
}

IJ TaxicabWithPaddingIndexModel::coordinate_of(Index idx) const {
    if (idx == PADDING_INDEX)
        return PADDING_COORD;

    auto coord = IJ {
            (idx - CELL_INDEX_ORIGIN) / get_shape().j.get(),
            (idx - CELL_INDEX_ORIGIN) % get_shape().j.get()
    };

    if (is_outside(coord))
        coord.state.set(IJState::INVALID);

    return coord;
}

void TaxicabWithPaddingIndexModel::TaxicabWithPaddingIndexModel::set_shape(IJ shape) {
    set_shape_(shape);
    set_size_(CELL_INDEX_ORIGIN + shape.i.get() * shape.j.get() );
}

// --- Padding node ----------

const topology::Node* TaxicabWithPaddingIndexModel::get_padding_node() const {
    return NodeContainer::get_node(PADDING_INDEX);
}

void TaxicabWithPaddingIndexModel::set_padding_node(topology::Node* node) {
    NodeContainer::set_node(node, PADDING_INDEX);
}
