#ifndef CPP__CONWAY_PADDING_H
#define CPP__CONWAY_PADDING_H

#include "indices/2d_taxicab/index_model.h"
#include <iostream>

class PaddingTaxicabIndex2DModel : public AbstractTaxicabIndex2DModel{
    /*
     *  Padding returns the 0'th index for all IJ out of the specified get_shape
     */

public:
    static bool covered_by(const IJ& point, const IJ & rect_endpoint) {
        if (point.i.get() < 0 || point.j.get() < 0)
            return false;
        if (point.i.get() >= rect_endpoint.i.get())
            return false;
        if (point.j.get() >= rect_endpoint.j.get())
            return false;
        return true;
    }

    virtual const Index get_size() const override {
        return get_size_();
    }

    virtual const IJ get_shape() const override {
        return get_shape_();
    }

    virtual void set_shape(IJ shape) override {
        set_shape_(shape);
        set_size_(shape.i.get() * shape.j.get() + 1); // +1 for padding Node (not represented in the grid)
    }

    virtual const Index index_of(const IJ & coord) const override {
        if (!covered_by(coord, get_shape_())) [[unlikely]] {
            return 0;
        }

        return coord.i.get() * get_shape_().j.get() + coord.j.get();
    }

    virtual const Index index_of(const IJ && coord) const override {
        return index_of(std::forward<const IJ&> (coord));
    }

    virtual const IJ coordinate_of(const Index & index) const override {
        return IJ(
                index / get_shape_().j.get(),
                index % get_shape_().j.get()
                );
    }

    virtual const IJ coordinate_of(const Index && index) const override {
        return coordinate_of(std::forward<const Index&> (index));
    }

};

#endif //CPP__CONWAY_PADDING_H
