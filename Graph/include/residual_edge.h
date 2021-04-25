#ifndef LAGER_GRAPH_LIBRARY_RESIDUAL_EDGE_H
#define LAGER_GRAPH_LIBRARY_RESIDUAL_EDGE_H

#include <functional>

#include "residual_node.h"


class ResidualGraph;

class ResidualEdge {
public:
    ResidualEdge() = delete;
    ResidualEdge(const ResidualEdge &other);

    int total_capacity() const;
    int remaining_capacity() const;
    int flow() const;
    ResidualNode &source();
    ResidualNode &destination();

    void add_flow(int amount);

private:
    friend class ResidualGraph;

    int _flow{};
    int _capacity{};
//    std::reference_wrapper<ResidualNode> _source;
//    std::reference_wrapper<ResidualNode> _destination;
    ResidualNode &_source;
    ResidualNode &_destination;

    ResidualEdge(ResidualNode &from, ResidualNode &to, int capacity);
};


#endif //LAGER_GRAPH_LIBRARY_RESIDUAL_EDGE_H