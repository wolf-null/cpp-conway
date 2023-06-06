#pragma once

#include <vector>

#include "indices/neighborhood_model.hpp"

class ConwayNeighborhoodModel : public NeighborhoodModel {
public:
    virtual std::vector<IJ> neighbor_indices_of(IJ index) override {
        std::vector <IJ> result;

        if (!index.is_valid())
            return result;

        for (int i = -1; i <= 1; ++ i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) [[unlikely]] {
                    continue;
                }

                result.emplace_back (i + index.i.get(), j + index.j.get());
            }
        }
        return result;
    }
};
