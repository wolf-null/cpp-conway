#ifndef CPP__KONWAY_NODE_H
#define CPP__KONWAY_NODE_H

class TopologyNodeInterface {
    /*
     * Can't make it virtual since templates can't override virtual methods.
     * But I also wanted to expose the interface, so I made a toy type:
     */
public:
    class DollType {};

    const int NOT_A_NEIGHBOR = -1;

    typedef DollType ValueType;
    const int MAX_NEIGHBORS = 0;
    typedef TopologyNodeInterface NodeType;

    explicit TopologyNodeInterface(const int id) : _id{id} {}
    ~TopologyNodeInterface() = default;

    const ValueType& value(){return _value;}
    void setValue(ValueType & value){_value = value;}

    auto subscribeTo(auto * neighbour) {return this;}
    auto unsubscribeFrom(const auto *neighbor) {return this;}

    int id(){return _id;}
    int neighbourCount() {return 0;}

    void printNeighbourIds() {std::cout << "\n";}

protected:
    const int _id;
    ValueType _value;

    int _neighborCount = 0;
    TopologyNodeInterface * _neighbors [1] {this};

    int neighbourIndex(const auto *neighbor) {return NOT_A_NEIGHBOR;}
    auto neighbourAt(const int neighborIndex = 0) {return this;}
    auto unsubscribeByIndex(const int neighborIndex = 0) {return this;}

};

template <class TopologyNodeCandidate>
concept TopologyNodeConcept = requires(TopologyNodeCandidate candidate) {
    std::derived_from<TopologyNodeCandidate, TopologyNodeInterface >;
};

#endif //CPP__KONWAY_NODE_H
