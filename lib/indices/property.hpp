#pragma once

#include <cstdlib>
#include <ostream>

template <typename T>
class Property {
    T coord_;
public:
    T get() const {return coord_;}
    void set(T coord){coord_ = coord;}

    explicit Property() = default;
    explicit Property(T coord) : coord_{coord} {};

    Property<T>& operator = (T coord) {set(coord);}
};

