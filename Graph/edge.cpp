#include "include/edge.h"

Edge::Edge(Node &source, Node &destination, int weight)
        : _source(std::reference_wrapper<Node>{source}),
          _destination(std::reference_wrapper<Node>{destination}),
          _weight(weight) {}

Edge::Edge(const Edge &other) = default;

int Edge::weight() const {
    return _weight;
}

Node &Edge::source() const {
    return _source;
}

Node &Edge::destination() const {
    return _destination;
}

bool Edge::operator==(const Edge &other) const {
    return this->_source.get() == other._source.get()
           && this->_destination.get() == other._destination.get();
}
