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
 *  Abstract class which adds additional way of indexing vector of Nodes with a pair of coordinates of type IJ.
 *  There is a distinguish: Index is a position of the node inside vector of nodes,
 *  whereas coordinates (a.k.a. IJ) are the position of the node on the cell field.
 *
 *  IndexModel provides mapping from Index to IJ and vice versa.
 *  @see IJ and IJState docs for IJ semantics.
 *  IndexModel implementation must override the following abstract methods:
 *  - virtual const Index index_of(const IJ coord) const
 *  - virtual const IJ coordinate_of(const Index index) const
 *
 *  IndexModel has shape() of type IJ which describes upper bounds for IJ i and j
 *  in which IndexModel organize one-one mapping IJ <--> Index.
 *  The lower bounds for IJ are assumed IJ(0, 0)
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

    virtual void set_shape(IJ shape); /**< CAUTION: causes vector of Nodes resize*/

    // -- Traverse --

    void map_IJ(std::function<void (IJ)> func) const;   /**< Maps all existing unique coordinates IJ which corresponds to the index*/


    /**
     * Maps all existing unique coordinates \ref IJ which corresponds to the \ref Index with func(IJ, Node*)
     * where first arg denotes the coordinate of the node (second arg).
     *
     * func(IJ current_node_index, Node* current_node) must return std::optional<Node*>.
     * If it has_value() the corresponding Node* at current_node_index is replaced by it.
     * */
    void overwriting_map_IJ(std::function<std::optional <topology::Node*> (IJ, topology::Node*)> func);

    // -- Node access --
    /**
     * Returns node by IJ \p coord using implementation of index_of(IJ).
     * If IJ.state is IJState::INVALID throws std::range_error immediately before index_of invoking
     * If there is no Node coordinate corresponding to allowed index std::range_error is raised
     * If index is valid but the node at the index was never set returns nullptr
     * */
    topology::Node* get_node(const IJ coord) const ;


    /**
     * Tries to set node to \p node at index corresponding to given \p coord using implementation of index_of(IJ).
     * If IJ.state is IJState::INVALID throws std::range_error immediately before index_of invoking
     * If there is no Node coordinate corresponding to allowed index std::range_error is raised
     */
    void set_node(topology::Node * node, const IJ coord) ;

    /**
     * Calls default constructor for all nodes from 0 to \ref get_size()
     * @tparam NodeType a type
     * @param reset_existed_nodes if false doesn't affect already initialized nodes
     *
     * @see \ref overwriting_map_IJ() as a more general method
     */
    template <typename NodeType=topology::Node>
    void assign_nodes(bool reset_existed_nodes = false);

    // -- Representation --

    /**
     * Returns a formatted JSON-like string of nodes and it's neighbors in form
     * list of dict {"node": [X], "neighbors": [X, X, ...]}
     * where X a \ref IJ represented with \ref IJ::to_string()
     */
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
