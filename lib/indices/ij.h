#pragma once

#include <string>

#include "indices/property.hpp"

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

    std::string to_string() const;

    bool operator == (const IJ& other) const;

    const bool is_valid() const;
};

std::ostream& operator << (std::ostream& ostream, const IJ& index);

