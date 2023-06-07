#include "node_container.h"

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

