#ifndef CPP__CONWAY_INDEX_MODEL_H
#define CPP__CONWAY_INDEX_MODEL_H

#include <ostream>
#include <iostream>
#include <functional>
#include <vector>
#include <stdexcept>
#include <optional>

#include "topology/node.h"
#include "indices/property.h"
#include "indices/ij.h"


typedef int Index;

class IndexModel {
public:
    using VectorOfNodes = std::vector <topology::Node*>;

private:
    Index size_;
    IJ shape_;
    VectorOfNodes * nodes_;

protected:

    // Size ------------------------------------------------------------------------------

    void set_size_(Index size) {
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

    const Index get_size_() const {
        return size_;
    }

    // Shape -----------------------------------------------------------------------------

    void set_shape_(IJ shape) {
        shape_ = shape;
    }

    const IJ get_shape_() const {
        return shape_;
    }


public:

    // To be implemented --------------------------------------

    virtual const Index index_of(const IJ coord) const = 0;
    virtual const IJ coordinate_of(const Index index) const = 0;

    // To be implemented --------------------------------------
    virtual void set_nodes_hook(VectorOfNodes * old_nodes, VectorOfNodes * new_nodes) {}

    // -- Constructors ----------------------------------------

    IndexModel() : size_{0}, shape_{0, 0, IJState::INVALID} {
        nodes_ = new VectorOfNodes {};
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

    void map_nodes(std::function<void (topology::Node*)> func) const {
        for (Index i = 0; i != get_size(); ++ i) {
            func(nodes_->at(i));
        }
    }

    void overwriting_map_IJ(std::function<std::optional <topology::Node*> (IJ, topology::Node*)> func) {
        for (Index i = 0; i != get_size(); ++ i) {
            IJ coord = coordinate_of(i);
            topology::Node * node = nullptr;
            if (i < get_size_())
                node = get_node(i);
            std::optional <topology::Node*> result = func(coord, node);
            if (result.has_value()) {
                set_node(result.value(), i);
            }
            result.reset();
        }
    }

    Index index_of(topology::Node * node) {
        auto found = std::find(nodes_->begin(), nodes_->end(), node);
        if (found == nodes_->end())
            return -1;
        return Index(found - nodes_->begin());
    }

    IJ coordinate_of(topology::Node * node) {
        auto index = index_of(node);
        if (index == -1)
            return IJ{0, 0, IJState::INVALID};

        return coordinate_of(index);
    }

    // -- Node access -----------------------------------------

    const VectorOfNodes* get_nodes() const {
        return nodes_;
    }

    void set_nodes(VectorOfNodes * nodes) {
        set_nodes_hook(nodes_, nodes);
        nodes_ = nodes;
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

    template <typename NodeType=topology::Node>
    void assign_nodes(bool reset_existed_nodes = false) {
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

    template <typename NodeType=topology::Node, typename ... InitArgs>
    void assign_nodes(bool reset_existed_nodes = false, InitArgs ... init_args) {
        auto constructor_invoker = [reset_existed_nodes, init_args...] (IJ coord, topology::Node * node) -> std::optional<topology::Node*> {
            if (node != nullptr) {
                if (reset_existed_nodes) {
                    delete node;
                } else {
                    return std::optional<topology::Node*> {std::nullopt};
                }
            }

            auto new_node = new NodeType{init_args...};
            return std::optional<topology::Node*>{new_node};
        };

        overwriting_map_IJ(constructor_invoker);
    }

    // -- Structure -----------------------------------------

    std::string neighborhood_to_str() {
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

};


#endif //CPP__CONWAY_INDEX_MODEL_H
