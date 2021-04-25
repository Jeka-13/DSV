#include <stdexcept>
#include "include/residual_edge.h"

ResidualEdge::ResidualEdge(const ResidualEdge &other) = default;

int ResidualEdge::total_capacity() const {
    return _capacity;
}

int ResidualEdge::remaining_capacity() const {
    return _capacity-_flow;
}

int ResidualEdge::flow() const {
    return _flow;
}

ResidualNode &ResidualEdge::source() {
    return _source;
}

ResidualNode &ResidualEdge::destination() {
    return _destination;
}

void ResidualEdge::add_flow(int amount) {
    if ((amount >= 0 && (amount+_flow) > _capacity) || (amount < 0 && (amount+_flow) < 0)) {
        throw std::logic_error("flow must not overflow available capacity");
    }

    _flow += amount;
}

ResidualEdge::ResidualEdge(ResidualNode &from, ResidualNode &to, int capacity)
        : _source(from), _destination(to), _flow(0), _capacity(capacity) {

    if (capacity < 0) {
        throw std::logic_error("edge capacity in residual graph must be non-negative");
    }
}
