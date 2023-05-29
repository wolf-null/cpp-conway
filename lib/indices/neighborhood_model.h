#ifndef CPP__CONWAY_NEIGHBORHOOD_MODEL_H
#define CPP__CONWAY_NEIGHBORHOOD_MODEL_H

#include <list>
#include <forward_list>
#include <functional>

#include "indices/ij.h"

class NeighborhoodModel {
    /*
     *  Describes an interface for a class providing neighbor indices for given index
     */

public:
    virtual std::forward_list <IJ> && neighbor_indices_of(IJ index) = 0;


};

#endif //CPP__CONWAY_NEIGHBORHOOD_MODEL_H
