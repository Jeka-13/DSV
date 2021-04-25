#include <unordered_map>

#include "include/residual_graph.h"

ResidualGraph::ResidualGraph(const Graph &graph) {
    std::unordered_map<int, int> node_index;
    int idx = 0;

    for (const Node &node : graph.nodes()) {
        _nodes.emplace_back(ResidualNode{node.id()});
        node_index.insert({node.id(), idx++ });
    }

    for (const Edge &edge : graph.edges()) {
        ResidualNode &source = _nodes[node_index[edge.source().id()]];
        ResidualNode &destination = _nodes[node_index[edge.destination().id()]];

        ResidualEdge new_edge{source, destination, edge.weight()};
        _edges.push_back(new_edge);
    }

    /**
     * This is done as another loop because ResidualNode contains refs to edges so it needs to know their addresses.
     * std::vector does resize when a new element is added and internal buffer doesn't have space for it. After resize
     * all objects are moved into a new memory chunk so previous addresses are lost.
     *
     * Pre-allocating std::vector is not possible because ResidualEdge does not have default constructor.
     */
    for (ResidualEdge &edge : _edges) {
        edge.source()._add_edge(edge);
        edge.destination()._add_edge(edge);
    }
}

ResidualGraph::ResidualGraph(const ResidualGraph &other) = default;

ResidualGraph::ResidualGraph(ResidualGraph &&other) noexcept {
    _nodes = std::move(other._nodes);
    _edges = std::move(other._edges);
}

std::vector<ResidualNode> &ResidualGraph::nodes() {
    return _nodes;
}

std::vector<ResidualEdge> &ResidualGraph::edges() {
    return _edges;
}
