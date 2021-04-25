#ifndef LAGER_GRAPH_LIBRARY_EDGE_H
#define LAGER_GRAPH_LIBRARY_EDGE_H

#include <functional>

#include "node.h"


class Edge {
public:
    Edge() = delete;
    Edge(Node &source, Node &destination, int weight);
    Edge(const Edge &other);

    bool operator==(const Edge &other) const;

    int weight() const;
    Node &source() const;
    Node &destination() const;

private:
    std::reference_wrapper<Node> _source;
    std::reference_wrapper<Node> _destination;
    int _weight{};
};


#endif //LAGER_GRAPH_LIBRARY_EDGE_H