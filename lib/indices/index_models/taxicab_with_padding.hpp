#ifndef CPP__CONWAY_TAXICAB_WITH_PADDING_HPP
#define CPP__CONWAY_TAXICAB_WITH_PADDING_HPP

#include "indices/index_model.hpp"

class TaxicabWithPaddingIndexModel : public IndexModel {
public:
    static const Index PADDING_INDEX = 0;
    static const Index CELL_INDEX_ORIGIN = PADDING_INDEX + 1;
    static const IJ PADDING_COORD;

    // ------------------------------------------------ Indexing -------------------------------------------------------

    inline bool is_outside(const IJ coord) const {
        if (coord.i.get() < 0 || coord.i.get() >= get_shape().i.get())
            return true;

        if (coord.j.get() < 0 || coord.j.get() >= get_shape().j.get())
            return true;

        return false;
    }

    Index index_of(const IJ coord) const override {
        if (coord.state.get() == IJState::PADDING)
            return PADDING_INDEX;

        if (is_outside(coord))
            return PADDING_INDEX;

        return CELL_INDEX_ORIGIN + coord.i.get() * get_shape().j.get() + coord.j.get();
    }

    IJ coordinate_of(const Index idx) const override {
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

    virtual void set_shape(IJ shape) override {
        set_shape_(shape);
        set_size_(CELL_INDEX_ORIGIN + shape.i.get() * shape.j.get() );
    }

    // ------------------------------------------------ Padding node ---------------------------------------------------

    const topology::Node* get_padding_node() const {
        return NodeContainer::get_node(PADDING_INDEX);
    }

    void set_padding_node(topology::Node* node) {
        NodeContainer::set_node(node, PADDING_INDEX);
    }

};

const IJ TaxicabWithPaddingIndexModel::PADDING_COORD {0, 0, IJState::PADDING};

#endif //CPP__CONWAY_TAXICAB_WITH_PADDING_HPP
