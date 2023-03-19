//
// Created by Mann on 17.03.2023.
//

#ifndef CPP__CONWAY_INDEX_POLICIES__TEST_H
#define CPP__CONWAY_INDEX_POLICIES__TEST_H

#include <stdexcept>
#include <string>
#include <iostream>

#include "indices/2d_taxicab/index_policies.h"

namespace indices_tests {
    template <class T>
    void check_flatten_unflatten(int h, int w, int length, int i, int j) {
        auto * p = static_cast <IndexPolicy*> (new T{h, w, length});
        int flattened = p->index_to_flat_index(IJ{.i = i, .j = j});
        IJ unflattened = p->flat_index_to_index(flattened);
        if (unflattened.i != i || unflattened.j != j)
            throw std::logic_error("Unflattened values " + unflattened.to_string() + " does not match origin: [" + std::to_string(i) + ", " + std::to_string(j) + "]. Intermediate value " + std::to_string(flattened));
    }

    template <class T>
    void check_unflatten_flatten(int h, int w, int length, int idx) {
        auto * p = static_cast <IndexPolicy*> (new T{h, w, length});
        IJ unflattened = p->flat_index_to_index(idx);
        int flattened = p->index_to_flat_index(unflattened);
        if (flattened != idx)
            throw std::logic_error("Flattened values " + std::to_string(flattened) + " does not match origin: " + std::to_string(idx) + " with intermediate value = " + unflattened.to_string() );
    }

    template <class T>
    void check_flatten(int h, int w, int length, int i, int j, int idx) {
        check_flatten_unflatten<T>(h, w, length, i, j);
        check_unflatten_flatten<T>(h, w, length, idx);
    }

    template <class T>
    void check_index_policy() {
        constexpr auto h = 10;
        constexpr auto w = 10;
        constexpr auto length = h * w;
        check_flatten<T>(h, w, length, 9, 2, 9*2);
    }


}

#endif //CPP__CONWAY_INDEX_POLICIES__TEST_H
