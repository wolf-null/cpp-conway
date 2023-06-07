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

//-------------------------------------- TEMPLATE IMPLEMENTATION ------------------------------------

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
    // TODO: Test

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

