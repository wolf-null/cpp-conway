#ifndef CPP__KONWAY_NODE_H
#define CPP__KONWAY_NODE_H

#include <stdexcept>

// Topology node role is a hint for various traverse mechanism telling what this node type exists for.

struct TopologyNodeRole {
    bool has_value;
};

class AbstractTopologyNode {
public:
    // TypeHints must be overridden in all concrete implementations
    typedef int ValueType;
    typedef AbstractTopologyNode NodeType;
    const int MAX_NEIGHBOURS = 0;

    AbstractTopologyNode() = default;
    AbstractTopologyNode(AbstractTopologyNode&) : AbstractTopologyNode() {
        throw std::domain_error("Copy constructor for AbstractTopologyNode was not overridden!");
    }
    ~AbstractTopologyNode() = default;

    [[nodiscard]] const int id () const {return _id;}
    [[nodiscard]] virtual const TopologyNodeRole role() const = 0;

    const int NOT_A_NEIGHBOR = -1;

private:

    void set_id(int id) {_id = id;}
    int _id = -1;

    friend class TopologyNodeDomain;
};


#endif //CPP__KONWAY_NODE_H
