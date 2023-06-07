#pragma once

#include "indices/index_model.h"

class TaxicabWithPaddingIndexModel : public IndexModel {
public:
    static const Index PADDING_INDEX = 0;
    static const Index CELL_INDEX_ORIGIN = PADDING_INDEX + 1;
    static const IJ PADDING_COORD;

    // ------------------------------------------------ Indexing -------------------------------------------------------

    inline bool is_outside(IJ coord) const ;

    Index index_of(IJ coord) const override ;

    IJ coordinate_of(Index idx) const override ;

    void set_shape(IJ shape) override ;

    // ------------------------------------------------ Padding node ---------------------------------------------------

    const topology::Node* get_padding_node() const;

    void set_padding_node(topology::Node* node) ;

};


