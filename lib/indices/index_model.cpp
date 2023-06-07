#include "index_model.h"


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
