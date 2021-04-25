#ifndef LAGER_GRAPH_LIBRARY_RESIDUAL_GRAPH_H
#define LAGER_GRAPH_LIBRARY_RESIDUAL_GRAPH_H

#include <vector>

#include "residual_node.h"
#include "residual_edge.h"
#include "graph.h"


/**
 * This class was designed to simplify process of finding Maxflow for a graph.
 * It is partially mutable using any object that is reachable from ResidualGraph object.
 *
 * Graph structure can not be changed after object creation while maxflow-specific features like
 * flow value can be changed.
 */
class ResidualGraph {
public:
    ResidualGraph() = delete;
    explicit ResidualGraph(const Graph &graph);
    ResidualGraph(const ResidualGraph &other);
    ResidualGraph(ResidualGraph &&other) noexcept;

    std::vector<ResidualNode> &nodes();
    std::vector<ResidualEdge> &edges();

private:
    std::vector<ResidualNode> _nodes;
    std::vector<ResidualEdge> _edges;
};


#endif //LAGER_GRAPH_LIBRARY_RESIDUAL_GRAPH_H