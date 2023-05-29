#ifndef CPP__CONWAY_IJ_H
#define CPP__CONWAY_IJ_H

#include "indices/property.h"

enum IJState {
    VALID,
    INVALID,
    PADDING
};

struct IJ{
    [[no_unique_address]] Property <int> i;
    [[no_unique_address]] Property <int> j;
    [[no_unique_address]] Property <IJState> state;

    explicit IJ() = default;
    explicit IJ(int i_value, int j_value, IJState valid=IJState::VALID) : i{i_value}, j{j_value}, state{valid} {};

    friend std::ostream& operator << (std::ostream& ostream, const IJ& index) {
        ostream << "(" << index.i.get() << ", " << index.j.get() << ")";
        return ostream;
    }

    bool operator == (const IJ& other) const {
        return other.i.get() == i.get() && other.j.get() == j.get();
    }

    const bool is_valid() const {
        return state.get() == IJState::VALID;
    }
};

#endif //CPP__CONWAY_IJ_H
