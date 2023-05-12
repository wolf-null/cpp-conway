#ifndef CPP__CONWAY_NODE_TESTS_H
#define CPP__CONWAY_NODE_TESTS_H

#include "node.h"
#include <iostream>
#include <stdexcept>

namespace topology {

struct NodeTest {
    class TestingNode : public Node {
    public:
        explicit TestingNode() : Node() {
            std::cout << "\tcreate node " << this << "\n";
        }

        explicit TestingNode(void * value_ptr) : TestingNode(){
            set_value_ptr(value_ptr);
        }

        ~TestingNode(){
            std::cout << "\tdelete node " << this << "\n";
        }
    };

    class test_failure : public std::exception {
    private:
        const std::string exc_message_;
    public:
        explicit test_failure(std::string &&description) : std::exception(), exc_message_{std::move(description)} {};
        [[nodiscard]] const char* what() const noexcept override {
            return exc_message_.c_str();
        }
    };


    static void test_neighbor_duplication(){
        std::cout << "TEST: test_neighbor_duplication\n";
        std::cout << "\n\ninit nodes\n";
        TestingNode node_a((void*)(new int(10)));
        TestingNode node_b((void*)(new int(20)));
        TestingNode node_c((void*)(new int(30)));

        std::cout << "\n\nadd neighbors\n";
        node_a.add_neighbor(&node_b);
        node_a.add_neighbor(&node_c);

        std::cout << "\n\ncheck neighbor doubling prevention\t";
        try {
            node_a.add_neighbor(&node_b);
            std::cout << "FAILED\n";
            throw test_failure("Adding already added Node didn't thrown an exception!");
        }
        catch (std::logic_error & exc) {
            std::cout << "OK\n";
        }

        std::cout << "removing all neighbors from a\t";
        node_a.remove_all_neighbors();
        std::cout << "OK\n";

        std::cout << "TEST FINISHED: test_neighbor_duplication\n";

    }

    static void test_neighbor_reduction() {
        std::cout << "TEST: test_neighbor_reduction\n";
        std::cout << "Init nodes\n";

        const int base_value_a = 10;
        const int base_value_b = 20;
        const int base_value_c = 30;
        const int base_value_sum = base_value_a + base_value_b + base_value_c;


        int value_a = base_value_a;
        int value_b = base_value_b;
        int value_c = base_value_c;

        TestingNode noda_a(&value_a);
        TestingNode noda_b(&value_b);
        TestingNode noda_c(&value_c);

        noda_a.add_neighbor(&noda_a);
        noda_a.add_neighbor(&noda_b);
        noda_a.add_neighbor(&noda_c);

        auto summator = [] (int& accumulated, int& value)-> void  {
            std::cout << "\tsummator\t";
            std::cout << "(" << accumulated << " += " << value << ")\n";
            accumulated += value;
        };

        std::cout << "Reducing\t";

        int sum = noda_a.neighbor_reduce<int>(summator, 0);

        std::cout << "OK\n";

        std::cout << "Resulted sum is " << sum << " must be equal to " << base_value_sum << "\n";
        assert(sum == base_value_sum);


        std::cout << "Check the origin values didn't change\t";
        assert(value_a == base_value_a);
        assert(value_b == base_value_b);
        assert(value_c == base_value_c);
        std::cout << "OK\n";

        std::cout << "TEST FINISHED: test_neighbor_reduction\n";
    }

    static void test_neighbor_destruction() {
        std::cout << "TEST: test_neighbor_destruction\n";
        std::cout << "\n\ninit nodes\n";
        auto node_a = new TestingNode (((void*)(new int(10))));
        TestingNode node_b((void*)(new int(20)));
        TestingNode node_c((void*)(new int(30)));

        std::cout << "\n\nadd neighbors\n";
        node_a->add_neighbor(&node_b);
        node_a->add_neighbor(&node_c);

        delete node_a;

        std::cout << "TEST FINISHED: test_neighbor_destruction\n";
    }

    static void test_all() {
        test_neighbor_duplication();
        test_neighbor_reduction();
        std::cout << "\nALL TESTS PASSED\n";
    }
};

}


#endif //CPP__CONWAY_NODE_TESTS_H

