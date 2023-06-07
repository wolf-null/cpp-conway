#pragma once

#include <ostream>
#include <iostream>
#include <functional>
#include <vector>
#include <stdexcept>
#include <optional>

#include "topology/node.hpp"
#include "indices/property.hpp"
#include "indices/ij.h"


/**
 *  Aliases how nodes are numerated. (default = int)
 *  The type used is required to support signed integer arithmetics
 *
 *  TODO: Find all arithmetic usecases
 *  TODO: Find a way to refactor to size_t
 */
using Index = int;

class NodeContainer {
public:
    using VectorOfNodes = std::vector <topology::Node*>;

private:
    Index size_;
    VectorOfNodes * nodes_;

protected:

    // Size ------------------------------------------------------------------------------

    void set_size_(Index size);
    Index get_size_() const;

    virtual void set_nodes_hook(VectorOfNodes * old_nodes, VectorOfNodes * new_nodes) {}


public:
    NodeContainer() : size_{0} {
        nodes_ = new VectorOfNodes {};
    };

    // -- Size --

    virtual Index get_size() const;

    // -- Indexing --

    Index index_of(topology::Node * node);

    // -- Traverse --

    void map_nodes(std::function<void (topology::Node*)> func) const;

    // -- Access --

    const VectorOfNodes* get_nodes() const ;

    void set_nodes(VectorOfNodes * nodes);

    topology::Node* get_node(const Index idx) const ;

    void set_node(topology::Node * node, const Index idx) ;

};

