#ifndef CPP__CONWAY_PADDING_TESTS_H
#define CPP__CONWAY_PADDING_TESTS_H

#include "indices/2d_taxicab/index_models/padding.h"
#include <cassert>
#include <iostream>

class TestPaddingTaxicabIndex2DModel {

public:
    // ------------------------------------------------ Shape tests -----------------------------------------------

    // -- set_shape -> get_shape -------------------------

    static void set_shape_get_shape_01() {
        const IJ shape {4, 3};
        PaddingTaxicabIndex2DModel model;
        model.set_shape(shape);
        auto resulted_shape = model.get_shape();
        assert(resulted_shape == shape);
    }

    static void set_shape_get_shape_02() {
        const IJ shape {3, 4};
        PaddingTaxicabIndex2DModel model;
        model.set_shape(shape);
        auto resulted_shape = model.get_shape();
        assert(resulted_shape == shape);
    }

    static void set_shape_get_shape() {
        std::cout << "set_shape_get_shape 01\n";
        set_shape_get_shape_01();
        std::cout << "set_shape_get_shape 02\n";
        set_shape_get_shape_02();
        std::cout << "set_shape_get_shape OK\n";
    }

    // -- set_shape -> get_size ---------------------------

    static void set_shape_get_size_01() {
        const int w{3}, h{4};
        const IJ shape {h, w};
        std::cout << "\t\tsetting size to " << shape << "\n";
        const Index expected_size = w * h + 1;
        PaddingTaxicabIndex2DModel model;
        model.set_shape(shape);
        auto resulted_size = model.get_size();
        std::cout << "\t\t" << resulted_size << " is expected to equal " << expected_size << "\n";
        assert(resulted_size == expected_size);
    }

    static void set_shape_get_size() {
        std::cout << "set_shape_get_size 01\n";
        set_shape_get_size_01();
        std::cout << "set_shape_get_size OK\n";
    }

    // -- all shape/size setters

    static void test_shape_size_setters() {
        set_shape_get_shape();
        set_shape_get_size();
    }
};

#endif //CPP__CONWAY_PADDING_TESTS_H
