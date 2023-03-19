#ifndef CPP__CONWAY_ABSTRACT_NODE_H
#define CPP__CONWAY_ABSTRACT_NODE_H

#include <stdexcept>

namespace topology {

    struct AbstractNodeRole {
        /* NodeRole holds additional info which can be accessed before casting AbstractNode to concrete Node subclasses */
        bool has_value;  // TODO: REFACTOR --> virtual func
        // ~ Tells if the concrete Node has .value() and .set_value() methods

        static constexpr int max_neighbours = 0;
    };


    class AbstractNode {
    public:
        virtual AbstractNodeRole* role() const = 0;
        AbstractNodeRole* get_role() {
            if (role_cache == nullptr)
                role_cache = role();
            return role_cache;
        }

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

        AbstractNodeRole * role_cache = nullptr;
    };
}

#endif //CPP__CONWAY_ABSTRACT_NODE_H

