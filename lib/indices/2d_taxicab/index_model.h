#ifndef CPP__CONWAY_INDEX_MODEL_H
#define CPP__CONWAY_INDEX_MODEL_H

#include <ostream>

#include "indices/property.h"
#include "indices/2d_taxicab/index_ij.h"


class AbstractTaxicabIndex2DModel {
    /*  -- Reasoning --
     * Node are assumed to be stored in a 1d list of Nodes within a certain position (called index).
     * Also, each Node on the grid is represented by the pair (i, j) (called coordinates / coords)
     * AbstractTaxicabIndexModel translates coords <--> indices
     *
     * Shape of the grid is described by shape (width, height),
     * all coords beyond 0 <= j < width and 0 <= i < height
     *
     * IndexModel2D assumes two coords (i, j) for the taxicab metric
     * The only assumed difference is how exactly the coords are translated into the index
     * */

    Index size_;
    IJ shape_;

    virtual void set_size_(Index size){size_ = size;}
    virtual void set_shape_(IJ shape){shape_ = shape;}

public:
    // -- Size

    const Index size() const {return size_;}

    void set_size(Index size){
        set_size_(size);
        set_shape_(coordinate_of(size_));
    }

    // -- Shape

    const IJ shape() const {return shape_;}

    void set_shape(IJ shape){
        set_shape_(shape);
        set_size_(index_of(shape_));
    }

    // -- Constructors

    AbstractTaxicabIndex2DModel() = delete;

    explicit AbstractTaxicabIndex2DModel(IJ shape){
        set_shape(shape);
    }

    explicit AbstractTaxicabIndex2DModel(Index size) {
        set_size(size);
    }

    // These methods must be implemented ---------------------------------------------------------------------

    virtual const Index index_of(IJ & coord) const = 0;
    virtual const Index index_of(IJ && coord) const = 0;

    virtual const IJ coordinate_of(Index & index) const = 0;
    virtual const IJ coordinate_of(Index && index) const = 0;
};


#endif //CPP__CONWAY_INDEX_MODEL_H
