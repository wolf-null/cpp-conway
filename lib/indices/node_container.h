#pragma once

#pragma once

#include <ostream>
#include <iostream>
#include <functional>
#include <vector>
#include <stdexcept>
#include <optional>

#include "topology/node.hpp"
#include "indices/property.hpp"
#include "indices/ij.hpp"


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

// ----------------------------------------------------------------------------------------------------
// -------------------------------------- IMPLEMENTATION ----------------------------------------------


// --- Size -------------------------------------------------------------------------------------------

Index NodeContainer::get_size_() const {
    return size_;
}

Index NodeContainer::get_size() const {
    return get_size_();
}

void NodeContainer::set_size_(Index size) {
    if (size == size_)
        return;

    if (size > size_) {
        nodes_->reserve(size);
        Index items_to_add = size - size_;
        while (items_to_add > 0) {
            nodes_->push_back(nullptr);
            items_to_add --;
        }
        size_ = size;
        return;
    }

    nodes_->erase(nodes_->begin() + size, nodes_->end());
    size_ = size;
}

// -- Traverse ------------------------------------------------------------------------------------

void NodeContainer::map_nodes(std::function<void (topology::Node*)> func) const {
    for (Index i = 0; i != get_size(); ++ i) {
        func(nodes_->at(i));
    }
}

// -- Coordinates ----------------------------------------------------------------------------------

Index NodeContainer::index_of(topology::Node * node) {
    auto found = std::find(nodes_->begin(), nodes_->end(), node);
    if (found == nodes_->end())
        return -1;
    return Index(found - nodes_->begin());
}

// -- Node access ----------------------------------------------------------------------------------

topology::Node* NodeContainer::get_node(const Index idx) const {
    return nodes_->at(idx);
}


void NodeContainer::set_node(topology::Node * node, const Index idx) {
    if (idx < 0 || idx >= get_size())
        throw std::range_error("Index " + std::to_string(idx) + " is out of bounds 0 .. " + std::to_string(get_size()));
    nodes_->operator[](idx) = node;
}

const NodeContainer::VectorOfNodes* NodeContainer::get_nodes() const {
    return nodes_;
}

void NodeContainer::set_nodes(VectorOfNodes * nodes) {
    set_nodes_hook(nodes_, nodes);
    nodes_ = nodes;
}

