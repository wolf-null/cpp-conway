#ifndef CPP__CONWAY_IJ_H
#define CPP__CONWAY_IJ_H

#include <string>

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

    std::string to_string() const {
        return "(" + std::to_string(i.get()) + ", " + std::to_string(j.get()) + ", " +  std::to_string(state.get()) + ")";
    }

    friend std::ostream& operator << (std::ostream& ostream, const IJ& index) {
        ostream << index.to_string();
        return ostream;
    }

    bool operator == (const IJ& other) const {
        if (state.get() == IJState::INVALID || other.state.get() == IJState::INVALID)
            return false;

        return other.i.get() == i.get() && other.j.get() == j.get() && state.get() == other.state.get();
    }

    const bool is_valid() const {
        return state.get() == IJState::VALID;
    }
};

#endif //CPP__CONWAY_IJ_H
