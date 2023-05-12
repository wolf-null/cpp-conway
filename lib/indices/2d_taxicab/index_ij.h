#ifndef CPP__CONWAY_INDEX_IJ_H
#define CPP__CONWAY_INDEX_IJ_H

#include "indices/property.h"


typedef size_t Index;

struct IJ{
    [[no_unique_address]] Property <int> i;
    [[no_unique_address]] Property <int> j;

    explicit IJ() = default;
    explicit IJ(int i_value, int j_value) : i{i_value}, j{j_value} {};

    friend std::ostream& operator << (std::ostream& ostream, const IJ& index) {
        ostream << "(" << index.i.get() << ", " << index.j.get() << ")";
        return ostream;
    }
};

#endif //CPP__CONWAY_INDEX_IJ_H
