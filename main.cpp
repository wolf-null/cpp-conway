#include <iostream>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <vector>

#include "lib/topology/node.h"
#include "lib/topology/node_tests.h"
#include "lib/topology/domain_tests.h"

#include <iostream>



class TestClass {
public:

    TestClass() {
        std::cout << "construct " << this << "\n";
    }

    TestClass(TestClass && base) {
        std::cout << "copy from " << &base << " into " << this << "\n";
    }

    TestClass(TestClass & base) {
        std::cout << "ref copy from " << &base << " into " << this << "\n";
    }


    ~TestClass() {
        std::cout << "destruct " << this << "\n";
    }
};

class TestSubclass : public TestClass {
public:

    TestSubclass() : TestClass() {
        std::cout << "s construct " << this << "\n";
    }

    TestSubclass(TestSubclass && base) {
        std::cout << "s copy from " << &base << " into " << this << "\n";
    }

    ~TestSubclass() {
        std::cout << "s destruct " << this << "\n";
    }
};


void tes1t() {
    std::cout << "start\n";
    std::vector<TestClass> vector;


    std::cout << "-- -- \n";
    std::cout << "build new TS\n";
    TestClass* tc0 = new TestClass{};
    std::cout << "Emplace TS\n";
    vector.emplace_back(*tc0);

    std::cout << "-- -- \n";
    std::cout << "build new TS\n";
    TestClass* tc = new TestSubclass{};
    std::cout << "Emplace TS\n";
    vector.emplace_back(*tc);
    std::cout << "-- -- \n";
    std::cout << "end of existence\n";
}

int main(int argc, char* argv[]) {
    tes1t();
    std::cout << "x_x\n";
    return 0;
}