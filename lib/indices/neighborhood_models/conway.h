#ifndef CPP__CONWAY_CONWAY_H
#define CPP__CONWAY_CONWAY_H

#include <forward_list>

#include "indices/neighborhood_model.h"

class ConwayNeighborhoodModel : public NeighborhoodModel {
public:
    virtual std::forward_list<IJ> && neighbor_indices_of(IJ index) override {
        std::forward_list <IJ> result;
        for (int i = -1; i <= 1; ++ i) {
            for (int j = -1; j != 1; ++j) {
                if (i == j) {
                    continue;
                }

                result.emplace_back (i + index.i.get(), j + index.j.get());
            }
        }
        return std::move(result);
    }
};

#endif //CPP__CONWAY_CONWAY_H
