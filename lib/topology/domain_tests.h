//
// Created by Mann on 21.03.2023.
//

#ifndef CPP__CONWAY_DOMAIN_TESTS_H
#define CPP__CONWAY_DOMAIN_TESTS_H

#include <iostream>

#include "node.h"
#include "domain.h"


void test_register_node() {
    Domain d;
    Node n;
    n.set_value_ptr(new int{10});
    int id = d.register_node(&n);
    assert (id == 1);
    assert(n.id() == 1);
}


// ----------------

struct X {
    static int last_auto_id;
    int auto_id;

    int * x_ = nullptr;
    X() :  x_{nullptr} {
        auto_id = last_auto_id;
        last_auto_id ++;
    };

    explicit X(int x)  : X() {
        x_ = new int(x);
    };

    explicit X(int *x) : X() {
        x_ = x;
    };

    X(X &&old)  noexcept : X(){
        x_ = old.x_;
        old.x_ = nullptr;
    };

    X& operator = (X && other)  noexcept {
        x_ = other.x_;
        other.x_ = nullptr;
        return *this;
    }

    X& operator = (X other)  noexcept {
        x_ = other.x_;
        return *this;
    }

    ~X() {
        x_ = nullptr;
    }


};

int X::last_auto_id = 0;


struct TestForwarding {

    void test_forwarding() {

        int counter = 665;

        auto g = [counter] () mutable -> X {counter ++; return X(counter);};

        Domain d;
        Node * n = d.make_node(g());

        assert(*static_cast<X*>(n->value_ptr())->x_ == 666);
    }

    friend Domain;
};

void test_domain() {
    TestForwarding{}.test_forwarding();
}

#endif //CPP__CONWAY_DOMAIN_TESTS_H
