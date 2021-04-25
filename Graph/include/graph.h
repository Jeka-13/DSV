#ifndef LAGER_GRAPH_LIBRARY_GRAPH_H
#define LAGER_GRAPH_LIBRARY_GRAPH_H

#include <vector>
#include <string>

#include "edge.h"
#include "node.h"


/**
 * Represents regular directed weighted graph
 *
 * This graph was designed to be mutated only using methods of the graph object itself.
 * Child Node and Edge objects are immutable.
 */
class Graph {
public:
    Graph();
    Graph(const Graph &other);
    Graph(Graph &&other) noexcept;

    static Graph read_from_file(const std::string &filepath);

    std::vector<Node> nodes() const;
    std::vector<Edge> edges() const;

    void add_node(int node_id);
    void add_edge(int source_node_id, int destination_node_id, int weight);
    void remove_node(int node_id);
    void remove_edge(int source_node_id, int destination_node_id);

private:
    std::vector<Node> _nodes;
    std::vector<Edge> _edges;
};


#endif //LAGER_GRAPH_LIBRARY_GRAPH_H