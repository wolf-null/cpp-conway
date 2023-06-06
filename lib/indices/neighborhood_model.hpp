#pragma once

#include <list>
#include <vector>
#include <functional>

#include "indices/ij.hpp"

class NeighborhoodModel {
public:
    virtual std::vector <IJ> neighbor_indices_of(IJ index) = 0;
};
