#ifndef CPP__CONWAY_INDEX_MODEL_H
#define CPP__CONWAY_INDEX_MODEL_H

#include <ostream>
#include <iostream>

#include "indices/property.h"
#include "indices/2d_taxicab/index_ij.h"


class AbstractTaxicabIndex2DModel {
    /*  -- Reasoning --
     * Node are assumed to be stored in a 1d list of Nodes within a certain position (called index).
     * Also, each Node on the grid is represented by the pair (i, j) (called coordinates / coords)
     * AbstractTaxicabIndexModel translates coords <--> indices
     *
     * Shape of the grid is described by get_shape (width, height),
     * all coords beyond 0 <= j < width and 0 <= i < height
     *
     * Size must return the number of Nodes required to be allocated
     *
     * IndexModel2D assumes two coords (i, j) for the taxicab metric
     * The only assumed difference is how exactly the coords are translated into the index
     * */

    Index size_;
    IJ shape_;

    static constexpr bool DEBUG = true;

protected:
    void set_size_(Index size){
        size_ = size;
        if constexpr (DEBUG)
            std::cout << "\t\t\tsize of " << this << " is set to " << size << "\n";
    }

    const Index get_size_() const {
        if constexpr (DEBUG)
            std::cout << "\t\t\tsize of " << this << " is " << size_ << "\n";
        return size_;
    }

    void set_shape_(IJ shape) {
        shape_ = shape;
        if constexpr (DEBUG)
            std::cout << "\t\t\tshape of " << this << " is set to " << shape << "\n";
    }

    const IJ get_shape_() const {
        if constexpr (DEBUG)
            std::cout << "\t\t\tshape of " << this << " is " << shape_ << "\n";
        return shape_;
    }

public:
    // -- Size

    virtual const Index get_size() const {
        return get_size_();
    }

    [[deprecated]] virtual void set_size(Index size){
        set_size_(size);
        set_shape_(coordinate_of(get_size_()));
    }

    // -- Shape

    virtual const IJ get_shape() const {
        return get_shape_();
    }

    virtual void set_shape(IJ shape){
        set_shape_(shape);
        set_size_(index_of(get_shape_()));
    }

    // -- Constructors

    //explicit AbstractTaxicabIndex2DModel() = delete;

    // These methods must be implemented ---------------------------------------------------------------------

    virtual const Index index_of(const IJ & coord) const = 0;
    virtual const Index index_of(const IJ && coord) const = 0;

    virtual const IJ coordinate_of(const Index & index) const = 0;
    virtual const IJ coordinate_of(const Index && index) const = 0;
};


#endif //CPP__CONWAY_INDEX_MODEL_H
