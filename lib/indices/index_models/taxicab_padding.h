#ifndef CPP__CONWAY_TAXICAB_PADDING_H
#define CPP__CONWAY_TAXICAB_PADDING_H

#include "indices/index_model.h"

class TaxicabWithPaddingIndexModel : public IndexModel {
public:
    static const Index PADDING_INDEX = 0;
    static const IJ PADDING_COORD;

    // ------------------------------------------------ Indexing -------------------------------------------------------

    inline bool is_outside(const IJ coord) const {
        if (coord.i.get() < 0 || coord.i.get() >= get_shape().i.get())
            return false;

        if (coord.j.get() < 0 || coord.j.get() >= get_shape().j.get())
            return false;

        return true;
    }

    virtual const Index index_of(const IJ coord) const override {
        if (is_outside(coord))
            return PADDING_INDEX;

        return PADDING_INDEX + coord.i.get() * get_shape().j.get() + coord.j.get();
    }

    virtual const IJ coordinate_of(const Index idx) const override {
        if (idx == PADDING_INDEX)
            return PADDING_COORD;

        auto coord = IJ {
                (idx - PADDING_INDEX) / get_shape().j.get(),
                (idx - PADDING_INDEX) % get_shape().j.get()
        };

        if (is_outside(coord))
            coord.state.set(IJState::INVALID);

        return coord;
    }

    // ------------------------------------------------ Padding node ---------------------------------------------------

    const topology::Node* get_padding_node() const {
        return get_node(PADDING_INDEX);
    }

    void set_padding_node(topology::Node* node) {
        set_node(node, PADDING_INDEX);
    }





};

const IJ TaxicabWithPaddingIndexModel::PADDING_COORD {0, 0, IJState::PADDING};

#endif //CPP__CONWAY_TAXICAB_PADDING_H
