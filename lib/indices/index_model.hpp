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
#include "indices/node_container.h"


/**
 *  Abstract class describing index model. Responsible for:
 *  - Conversion between coordinates <--> indices (the index model)
 *  - Storing node (topology:Node) instances
 *  - Providing basic methods for traversing stored nodes
 *
 *  Reasoning for uniting those three responsibilities is their mutual cross-dependence
 *
 *  The following index-modelling methods are to be implemented:
 *  - virtual const Index index_of(const IJ coord) const
 *  - virtual const IJ coordinate_of(const Index index) const
 *
 *  TODO: Refactor std::vector <topology::Node*> --> std::vector <std::unique_ptr <topology::Node*>>
 */
class IndexModel : public NodeContainer{

private:
    IJ shape_;


protected:

    // Shape -----------------------------------------------------------------------------

    void set_shape_(IJ shape);
    IJ get_shape_() const;

public:

    // -- Constructors --

    IndexModel() : shape_{0, 0, IJState::INVALID}, NodeContainer{} {};

    // -- Indexing --

    virtual Index index_of(const IJ coord) const = 0;

    virtual IJ coordinate_of(const Index index) const = 0;

    IJ coordinate_of(topology::Node * node);


    // -- Shape --

    virtual IJ get_shape() const;

    virtual void set_shape(IJ shape);

    // -- Traverse --

    void map_IJ(std::function<void (IJ)> func) const;


    void overwriting_map_IJ(std::function<std::optional <topology::Node*> (IJ, topology::Node*)> func);

    // -- Node access --

    topology::Node* get_node(const IJ coord) const ;

    void set_node(topology::Node * node, const IJ coord) ;

    template <typename NodeType=topology::Node>
    void assign_nodes(bool reset_existed_nodes = false);

    template <typename NodeType=topology::Node, typename ... InitArgs>
    void assign_nodes(bool reset_existed_nodes = false, InitArgs ... init_args) ;

    // -- Representation --

    std::string neighborhood_to_str();

};

// ----------------------------------------------------------------------------------------------------
// -------------------------------------- IMPLEMENTATION ----------------------------------------------


void IndexModel::set_shape_(IJ shape) {
    shape_ = shape;
}

IJ IndexModel::get_shape_() const {
    return shape_;
}

IJ IndexModel::get_shape() const {
    return get_shape_();
}

void IndexModel::set_shape(IJ shape){
    set_shape_(shape);
    set_size_(index_of(get_shape_()));
}

// -- Traverse ------------------------------------------------------------------------------------

void IndexModel::map_IJ(std::function<void (IJ)> func) const {
    for (Index i = 0; i != get_size(); ++ i) {
        func(coordinate_of(i));
    }
}

void IndexModel::overwriting_map_IJ(std::function<std::optional <topology::Node*> (IJ, topology::Node*)> func) {
    for (Index i = 0; i != get_size(); ++ i) {
        IJ coord = coordinate_of(i);
        topology::Node * node = nullptr;
        if (i < get_size_())
            node = NodeContainer::get_node(i);
        std::optional <topology::Node*> result = func(coord, node);
        if (result.has_value()) {
            NodeContainer::set_node(result.value(), i);
        }
        result.reset();
    }
}

// -- Coordinates ----------------------------------------------------------------------------------

IJ IndexModel::coordinate_of(topology::Node * node) {
    auto index = NodeContainer::index_of(node);
    if (index == -1)
        return IJ{0, 0, IJState::INVALID};

    return coordinate_of(index);
}

// -- Node access ----------------------------------------------------------------------------------

topology::Node* IndexModel::get_node(const IJ coord) const {
    return NodeContainer::get_node(index_of(coord));
}

void IndexModel::set_node(topology::Node * node, const IJ coord) {
    auto idx = index_of(coord);
    NodeContainer::set_node(node, idx);
}

template <typename NodeType>
void IndexModel::assign_nodes(bool reset_existed_nodes) {
    auto constructor_invoker = [reset_existed_nodes] (IJ coord, topology::Node * node) -> std::optional<topology::Node*> {
        if (node != nullptr) {
            if (reset_existed_nodes) {
                delete node;
            } else {
                return std::optional<topology::Node*> {std::nullopt};
            }
        }

        return std::optional<topology::Node*>(new NodeType{});
    };

    overwriting_map_IJ(constructor_invoker);
}

template <typename NodeType, typename ... InitArgs>
void IndexModel::assign_nodes(bool reset_existed_nodes, InitArgs ... init_args) {
    auto constructor_invoker = [reset_existed_nodes, init_args...] (IJ coord, topology::Node * node) -> std::optional<topology::Node*> {
        if (node != nullptr) {
            if (reset_existed_nodes) {
                delete node;
            } else {
                return std::optional<topology::Node*> {std::nullopt};
            }
        }

        return std::optional<topology::Node*>(new NodeType{init_args...});
    };

    overwriting_map_IJ(constructor_invoker);
}

// -- Structure ------------------------------------------------------------------------------------

std::string IndexModel::neighborhood_to_str() {
    std::string result = "[\n";
    auto f = [&result, this] (IJ coord) -> void {
        result += "[" + coord.to_string() + ",\t[";
        auto * node = this->get_node(coord);
        for (auto *neighbor : node->neighbors_) {
            IJ neighbor_coordinate = coordinate_of(neighbor);
            result += neighbor_coordinate.to_string() + ", ";
        }
        result += "],\n";
    };

    map_IJ(f);
    result += "]";
    return result;
}
