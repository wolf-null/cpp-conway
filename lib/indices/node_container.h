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


/**
 * A class for containing Nodes.
 *
 * Not responsible for construction/initialization of nodes and for their destruction,
 * Since topology::Node is more like an interface, it's implementations might have initialization
 * of any complexity, which can't be beforehand-covered by a constructor.
 *
 * TODO: Securify contained Node ownership.
 */
class NodeContainer {
public:
    using VectorOfNodes = std::vector <topology::Node*>;  /**< TODO: Refactor to shared_ptr<*/

private:
    Index size_;
    VectorOfNodes * nodes_;

protected:

    // Size ------------------------------------------------------------------------------

    void set_size_(Index size);
    Index get_size_() const;

    virtual void set_nodes_hook(VectorOfNodes * old_nodes, VectorOfNodes * new_nodes) {} /**< Triggered when set_nodes is called*/


public:
    NodeContainer() : size_{0} {
        nodes_ = new VectorOfNodes {};
    };

    // -- Size --

    virtual Index get_size() const;

    // -- Indexing --

    Index index_of(topology::Node * node);

    // -- Traverse --

    void map_nodes(std::function<void (topology::Node*)> func) const; /**< apply void func(Node) to all contained nodes*/

    // -- Access --

    const VectorOfNodes* get_nodes() const ;

    void set_nodes(VectorOfNodes * nodes);

    topology::Node* get_node(const Index idx) const ; /**< returns Node* by index, throws std::range_error if out of range. NOTE: Node at idx can be not initialized, so nullptr doesn't mean out of range.*/

    void set_node(topology::Node * node, const Index idx) ;

};

