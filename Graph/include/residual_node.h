#ifndef LAGER_GRAPH_LIBRARY_RESIDUAL_NODE_H
#define LAGER_GRAPH_LIBRARY_RESIDUAL_NODE_H

#include <vector>
#include <memory>


class ResidualGraph;
class ResidualEdge;

class ResidualNode {
public:
    ResidualNode() = delete;
    ResidualNode(const ResidualNode &other);

    int id() const;
    std::vector<std::reference_wrapper<ResidualEdge>> outgoing_edges();
    std::vector<std::reference_wrapper<ResidualEdge>> ingoing_edges();

    ResidualEdge &get_edge_to(int x);
    ResidualEdge &get_edge_from(int x);

private:
    friend class ResidualGraph;

    int _id;
//    std::shared_ptr<std::vector<ResidualEdge>> _ingoing_ptr;
//    std::shared_ptr<std::vector<ResidualEdge>> _outgoing_ptr;
    std::vector<std::reference_wrapper<ResidualEdge>> _ingoing_edges;
    std::vector<std::reference_wrapper<ResidualEdge>> _outgoing_edges;


    explicit ResidualNode(int id);
    void _add_edge(ResidualEdge &edge);
};


#endif //LAGER_GRAPH_LIBRARY_RESIDUAL_NODE_H