#pragma once

#include <cstdlib>
#include <ostream>

/**
 * Coordinate property
 * Provides general get/set interface for property access.
 * TODO: Do we really need this one? This is not Python
 * */
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

