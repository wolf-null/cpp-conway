//
// Created by Mann on 20.03.2023.
//

#ifndef CPP__CONWAY_NODE_TESTS_H
#define CPP__CONWAY_NODE_TESTS_H

#include "node.h"


void test_node_state() {
    NodeState s{.can_evaluate=true};
    s.can_evaluate = false;
    Node node;
    node.set_state(s);
    NodeState p{node.state()};
    assert (p.can_evaluate == false);
    p.can_evaluate = true;
    assert (p.can_evaluate == true);
}

void test_value_basetype() {
    Node node;
    node.set_value_ptr(static_cast<void*> (new int {10}), ValueDescription({.type_id=ValueTypeID::INT}));
    int val = *static_cast<int*> (node.value_ptr());
    assert(val == 10);
}

void test_value_struct() {
    struct TestVirtualStruct {
        int value = 10;
        virtual int do_something_abstract(int val) = 0;
        void do_something() {value = do_something_abstract(value);}
    };

    struct TestStructA : public TestVirtualStruct {
        virtual int do_something_abstract(int val) override {return val + 1;}
    };

    struct TestStructB : public TestVirtualStruct {
        int custom_term = 10;
        virtual int do_something_abstract(int val) override {return val + custom_term;}
        int anything = 12431234;
    };

    Node node;
    TestStructA * str = new TestStructA();
    node.set_value_ptr(str);
    TestVirtualStruct * ostr = static_cast<TestVirtualStruct*> (node.value_ptr());
    ostr->do_something();

    assert(str->value == 11);

    Node node2;
    TestStructB * str2 = new TestStructB();
    node2.set_value_ptr(str2);
    TestVirtualStruct * ostr2 = static_cast<TestVirtualStruct*> (node2.value_ptr());
    ostr2->do_something();

    assert(str2->value == 20);
}

void test_neighbor_reduce_lval(){
    Node a; a.set_value_ptr(new int (1));
    Node b; b.set_value_ptr(new int (10));
    Node c; c.set_value_ptr(new int (100));

    a.neighbors_.push_back(&a);
    a.neighbors_.push_back(&b);
    a.neighbors_.push_back(&c);

    auto func = [](int a, int b) -> int {return a + b;};
    int result = a.neighbor_reduce<int>(func);

    assert (result == 111);

    auto func2 = [](int& a, int &b) -> int& {a += b; return a;};
    int base_val2 = 1000;
    int result2 = a.neighbor_reduce<int>(func2, base_val2);

    assert (result2 == 1111);
    assert (base_val2 == 1111);
}


void test_neighbor_reduce_selected(){
    Node a; a.set_value_ptr(new int (1));
    Node b; b.set_value_ptr(new int (10));
    Node c; c.set_value_ptr(new int (100));

    a.neighbors_.push_back(&a);
    a.neighbors_.push_back(&b);
    a.neighbors_.push_back(&c);

    auto func2 = [](int& a, int &b) -> int& {a += b; return a;};
    int result2 = Node::node_reduce<int>(std::move(a.neighbors_), func2, 1000);

    assert (result2 == 1111);
}

void test() {
    test_node_state();
    test_value_basetype();
    test_value_struct();
    test_neighbor_reduce_lval();
}


#endif //CPP__CONWAY_NODE_TESTS_H
