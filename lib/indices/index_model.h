#ifndef CPP__CONWAY_INDEX_MODEL_H
#define CPP__CONWAY_INDEX_MODEL_H

#include <ostream>
#include <iostream>
#include <functional>
#include <vector>
#include <stdexcept>

#include "topology/node.h"
#include "indices/property.h"
#include "indices/ij.h"


typedef int Index;

class IndexModel {
private:
    Index size_;
    IJ shape_;
    std::vector <topology::Node*> * nodes_;

protected:

    void set_size_(Index size) {
        if (size == size_)
            return;
        realloc_(size_, size);
        size_ = size;
    }

    const Index get_size_() const {
        return size_;
    }

    void set_shape_(IJ shape) {
        shape_ = shape;
    }

    const IJ get_shape_() const {
        return shape_;
    }

    virtual void realloc_(Index old_size, Index new_size) {
        nodes_->reserve(new_size);
    }

public:

    // To be implemented --------------------------------------

    virtual const Index index_of(const IJ coord) const = 0;
    virtual const IJ coordinate_of(const Index index) const = 0;

    // -- Constructors ----------------------------------------

    IndexModel() : size_{0}, shape_{0, 0, IJState::INVALID} {
        nodes_ = new std::vector <topology::Node*> {};
    };

    // -- Size ------------------------------------------------

    virtual const Index get_size() const {
        return get_size_();
    }

    // -- Shape -----------------------------------------------

    virtual const IJ get_shape() const {
        return get_shape_();
    }

    virtual void set_shape(IJ shape){
        set_shape_(shape);
        set_size_(index_of(get_shape_()));
    }

    // -- Traverse --------------------------------------------

    void map_IJ(std::function<void (IJ)> func) const {
        for (Index i = 0; i != get_size(); ++ i) {
            func(coordinate_of(i));
        }
    }

    // -- Node access -----------------------------------------

    const std::vector <topology::Node*>* get_nodes() const {
        return nodes_;
    }

    void set_nodes(std::vector <topology::Node*> * nodes) {
        nodes_ = nodes;
        // TODO: Realloc? Check size match?
    }

    topology::Node* get_node(const Index idx) const {
        return nodes_->at(idx);
    }

    topology::Node* get_node(const IJ coord) const {
        return get_node(index_of(coord));
    }

    void set_node(topology::Node * node, const Index idx) {
        if (idx < 0 || idx >= get_size())
            throw std::range_error("Index " + std::to_string(idx) + " is out of bounds 0 .. " + std::to_string(get_size()));
        nodes_->operator[](idx) = node;
    }

    void set_node(topology::Node * node, const IJ coord) {
        auto idx = index_of(coord);
        set_node(node, idx);
    }



};


#endif //CPP__CONWAY_INDEX_MODEL_H
