#include <stdexcept>
#include <functional>
#include <memory>
#include <algorithm>

#include "include/node.h"
#include "include/edge.h"

Node::Node(int _id) : _id(_id) {
    _ingoing_ptr = std::make_shared<std::vector<Edge>>();
    _outgoing_ptr = std::make_shared<std::vector<Edge>>();
}

Node::Node(const Node &other) = default;

int Node::id() const {
    return _id;
}

std::vector<Edge> Node::outgoing_edges() const {
    return *_outgoing_ptr;
}

std::vector<Edge> Node::ingoing_edges() const {
    return *_ingoing_ptr;
}

void Node::_add_edge(const Edge &edge) {
    if (edge.source().id() != _id && edge.destination().id() != _id) {
        throw std::logic_error("given edge does not connects with current node");
    }

    if (edge.source().id() == _id) {
        if (std::any_of(this->_outgoing_ptr->begin(), this->_outgoing_ptr->end(),
                        [&edge](const Edge &e){ return edge == e; })) {
            throw std::logic_error("node already contains an outgoing edge to the same destination");
        }

        _outgoing_ptr->emplace_back(edge);
    }
    if (edge.destination().id() == _id) {
        if (std::any_of(this->_ingoing_ptr->begin(), this->_ingoing_ptr->end(),
                        [&edge](const Edge &e){ return edge == e; })) {
            throw std::logic_error("node already contains an ingoing edge from the same source");
        }

        _ingoing_ptr->emplace_back(edge);
    }
}

void Node::_remove_edge(const Edge &edge) {
    if (edge.source().id() != _id && edge.destination().id() != _id) {
        throw std::logic_error("given edge does not connects with current node");
    }

    if (edge.source().id() == _id) {
        auto it = std::find(this->_outgoing_ptr->begin(), this->_outgoing_ptr->end(), edge);
        if (it == this->_outgoing_ptr->end()) {
            throw std::logic_error("given edge is not registered inside this node");
        }

        this->_outgoing_ptr->erase(it);
    }
    if (edge.destination().id() == _id) {
        auto it = std::find(this->_ingoing_ptr->begin(), this->_ingoing_ptr->end(), edge);
        if (it == this->_ingoing_ptr->end()) {
            throw std::logic_error("given edge is not registered inside this node");
        }

        this->_ingoing_ptr->erase(it);
    }
}

bool Node::operator==(const Node &other) const {
    return this->_id == other._id;
}
