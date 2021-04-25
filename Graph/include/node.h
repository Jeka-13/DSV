#ifndef LAGER_GRAPH_LIBRARY_NODE_H
#define LAGER_GRAPH_LIBRARY_NODE_H

#include <vector>
#include <memory>


class Edge;

class Node {
public:
    explicit Node(int id);
    Node(const Node &other);

    bool operator==(const Node &other) const;

    int id() const;
    std::vector<Edge> outgoing_edges() const;
    std::vector<Edge> ingoing_edges() const;

private:
    friend class Graph;

    int _id{};
    std::shared_ptr<std::vector<Edge>> _ingoing_ptr;
    std::shared_ptr<std::vector<Edge>> _outgoing_ptr;

    void _add_edge(const Edge &edge);
    void _remove_edge(const Edge &edge);
};


#endif //LAGER_GRAPH_LIBRARY_NODE_H