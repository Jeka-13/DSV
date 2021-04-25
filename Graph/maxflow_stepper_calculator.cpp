#include <vector>
#include <climits>
#include <algorithm>

#include "include/maxflow_stepper_calculator.h"

#define NOT_VISITED 0
#define EXPLORED    1
#define VISITED     2

using namespace std;

MaxflowStepperCalculator::MaxflowStepperCalculator(const Graph &graph, int source_id, int sink_id)
        : _graph(ResidualGraph(graph)), _maximum_flow_value(0), _source_id(source_id), _sink_id(sink_id) {

    _prev.assign(graph.nodes().size(), -1);
}

static inline void enque(vector<int> &visited, queue<int> &q, int x) {
    q.push(x);
    visited[x] = EXPLORED;
}

static inline int deque(vector<int> &visited, queue<int> &q) {
    int x = q.front();
    q.pop();
    visited[x] = VISITED;
    return x;
}

/**
 * Attempts to reach sink node starting from source.
 * Verification is done using BFS algorithm.
 */
bool MaxflowStepperCalculator::is_sink_reachable() {
    vector<int> visited(_graph.nodes().size(), NOT_VISITED);
    queue<int> q;

    enque(visited, q, _source_id);
    _prev[_source_id] = -1;
    while (!q.empty()) {
        int v = ::deque(visited, q);

        for (ResidualEdge &e : _graph.nodes()[v].outgoing_edges()) {

            int u = e.destination().id();
            if (visited[u] == NOT_VISITED && e.remaining_capacity() > 0) {
                enque(visited, q, u);
                _prev[u] = v;
            }
        }
    }

    return visited[_sink_id] == VISITED;
}

bool MaxflowStepperCalculator::finished() {
    return !is_sink_reachable();
}

MaxflowCalculationResults MaxflowStepperCalculator::do_step() {
    if (finished()) {
        return MaxflowCalculationResults(_maximum_flow_value, 0, vector<int>());
    }

    vector<int> augmented_path_ids;
    vector<ResidualNode> &nodes = _graph.nodes();

    /* find maximum delta across path source->sink */
    int delta = INT_MAX;
    for (ResidualNode *x = &nodes[_sink_id]; x->id() != _source_id; ) {
        int previous_node_id = _prev[x->id()];
        ResidualEdge &edge = x->get_edge_from(previous_node_id);

        delta = min(delta, edge.remaining_capacity());

        x = &edge.source();
    }

    /* augment path from source->sink with new delta */
    for (ResidualNode *x = &nodes[_sink_id]; x->id() != _source_id; ) {
        int previous_node_id = _prev[x->id()];
        ResidualEdge &edge = x->get_edge_from(previous_node_id);

        edge.add_flow(delta);
        augmented_path_ids.emplace_back(x->id());

        x = &edge.source();
    }
    augmented_path_ids.emplace_back(_source_id);
    std::reverse(augmented_path_ids.begin(), augmented_path_ids.end());
    _maximum_flow_value += delta;

    return MaxflowCalculationResults(_maximum_flow_value, delta, augmented_path_ids);
}

int MaxflowStepperCalculator::get_current_maximum_flow() const {
    return _maximum_flow_value;
}
