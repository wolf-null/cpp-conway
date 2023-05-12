#include "lib/topology/node.h"
#include "lib/topology/node_tests.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    std::vector <int> a;
    a.push_back(0);
    a.push_back(1);
    a.push_back(2);
    auto found = std::find(a.begin(), a.end(), 3);
    if (found == a.end())
    {
        std::cout << "none\n";
        return 0;
    }
    a.erase(found);

    for(int k : a){
        std::cout << k << " ";
    }
    return 0;
}
