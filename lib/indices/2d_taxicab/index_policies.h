//
// Created by Mann on 17.03.2023.
//

#ifndef CPP__CONWAY_INDEX_POLICIES_H
#define CPP__CONWAY_INDEX_POLICIES_H

#include "assets.h"
#include <stdexcept>
#include <string>

class IndexPolicy {
private:
    int w_ = 0;
    int h_ = 0;
    int length_ = 0;

public:
    IndexPolicy() = default;
    explicit IndexPolicy(int h, int w, int length) : IndexPolicy() { set_boundaries(h, w, length);};

    virtual int index_to_flat_index(IJ ij) const = 0;
    virtual IJ flat_index_to_index(int idx) const = 0;

    virtual void set_boundaries(int h, int w, int length) {
        h_ = h;
        w_ = w;
        length_ = length;
    }

    virtual void check_boundaries(IJ &ij, int length) const {
        int flattened = index_to_flat_index(ij);
        if ( 0 < flattened && flattened < length) {
            return;
        }
        throw std::range_error("Index " + ij.to_string() + " has flattened to " + std::to_string(flattened) + " which is out of bounds: " + std::to_string(this->length()));
    }

    virtual void check_boundaries(IJ &ij) const {
        check_boundaries(ij, length());
    }

    int w() const {return w_;}
    int h() const {return h_;}
    int length() const {return length_;}
};

class IndexPolicyLinear : public IndexPolicy{
public:
    IndexPolicyLinear() = default;
    explicit IndexPolicyLinear(int h, int w, int length) : IndexPolicy() { set_boundaries(h, w, length);};

    virtual int index_to_flat_index(IJ ij) const {
        return ij.i * w() + ij.j;
    };

    virtual IJ flat_index_to_index(int idx) const {
        return {.i = idx / w(), .j = idx % w()};
    }
};

#endif //CPP__CONWAY_INDEX_POLICIES_H
