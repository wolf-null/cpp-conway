#ifndef CPP__CONWAY_ABSTRACT_NODE_H
#define CPP__CONWAY_ABSTRACT_NODE_H

#include <stdexcept>

namespace topology {

    struct NodeRole {
        /* NodeRole holds additional info which can be access before casting AbstractNode to concrete Node subclasses */

        bool has_value;
        // ~ Tells if the concrete Node has .value() and .set_value() methods
    };


    class AbstractNode {
    public:
        [[nodiscard]] virtual const NodeRole role() const = 0;
        const int id() const { return _id; }

        AbstractNode() = default;
        AbstractNode(AbstractNode &) : AbstractNode() {
            throw std::domain_error("Copy constructor for AbstractNode was not overridden!");
        }
        ~AbstractNode() = default;

        const int NOT_A_NEIGHBOR = -1;

    private:
        int _id = -1;
        void set_id(int id) { _id = id; }

        friend class NodeDomain; // NodeDomain uses set_id()
    };
}

#endif //CPP__CONWAY_ABSTRACT_NODE_H

