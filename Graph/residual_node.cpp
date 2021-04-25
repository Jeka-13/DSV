#include <stdexcept>
#include "include/residual_node.h"
#include "include/residual_edge.h"

ResidualNode::ResidualNode(const ResidualNode &other) = default;

int ResidualNode::id() const {
    return _id;
}

std::vector<std::reference_wrapper<ResidualEdge>> ResidualNode::outgoing_edges() {
    return _outgoing_edges;
}

std::vector<std::reference_wrapper<ResidualEdge>> ResidualNode::ingoing_edges() {
    return _ingoing_edges;
}

ResidualNode::ResidualNode(int id)
        : _id(id) {}

void ResidualNode::_add_edge(ResidualEdge &edge) {
    if (edge.source()._id != _id && edge.destination()._id != _id) {
        throw std::logic_error("given edge is not connected with current node");
    }

    if (edge.source()._id == _id) {
        _outgoing_edges.emplace_back(edge);
    } else {
        _ingoing_edges.emplace_back(edge);
    }
}

ResidualEdge &ResidualNode::get_edge_to(int x) {
    for (ResidualEdge &edge : _outgoing_edges) {
        if (edge.destination().id() == x) {
            return edge;
        }
    }

    throw std::logic_error("current node is not connected with given node");
}

ResidualEdge &ResidualNode::get_edge_from(int x) {
    for (ResidualEdge &edge : _ingoing_edges) {
        if (edge.source().id() == x) {
            return edge;
        }
    }

    throw std::logic_error("current node is not connected with given node");
}
