#include <stdexcept>
#include <utility>
#include <algorithm>
#include <climits>

#include "include/graph.h"

#define DELETED INT_MIN

static std::vector<Node>::iterator find_node_with_id(std::vector<Node> &nodes, int node_id);

Graph::Graph() = default;

Graph::Graph(const Graph &other) {
    for (auto &node : other.nodes()) {
        this->add_node(node.id());
    }
    for (auto &edge : other.edges()) {
        this->add_edge(edge.source().id(), edge.destination().id(), edge.weight());
    }
}

Graph::Graph(Graph &&other) noexcept {
    this->_nodes = std::move(other._nodes);
    this->_edges = std::move(other._edges);
}

Graph Graph::read_from_file(const std::string &filepath) {
    Graph result;

    FILE *input = fopen(filepath.c_str(), "r");
    if (input == nullptr) {
        throw std::runtime_error("cannot open input file");
    }

    int n, m, is_directed, is_weighted;
    fscanf(input, "%d %d %d %d", &n, &m, &is_directed, &is_weighted);

    if (n < 0 || m < 0) {
        throw std::out_of_range("at least one of graph dimensions has negative value");
    }
    if (!is_directed) {
        throw std::logic_error("undirected graphs are not supported for this moment");
    }
    if (!is_weighted) {
        throw std::logic_error("unweighted graphs are not supported for this moment");
    }

    for (int i = 0; i < n; i++) {
        result.add_node(i);
    }

    for (int i = 0; i < m; i++) {
        int x, y, w;
        fscanf(input, "%d %d %d", &x, &y, &w);

        if (x < 0 || x >= n) {
            throw std::out_of_range("one of edges has invalid source id");
        }
        if (y < 0 || y >= n) {
            throw std::out_of_range("one of edges has invalid destination id");
        }

        result.add_edge(x, y, w);
    }

    return result;
}

std::vector<Node> Graph::nodes() const {
    std::vector<Node> result;
    std::copy_if(this->_nodes.begin(), this->_nodes.end(), std::back_insert_iterator<std::vector<Node>>(result),
                 [](const Node &n) { return n.id() != DELETED; });
    return result;
}

std::vector<Edge> Graph::edges() const {
    return this->_edges;
}

void Graph::add_node(int node_id) {
    /* check if there is no node with the same id */
    if (find_node_with_id(this->_nodes, node_id) != this->_nodes.end()) {
        throw std::logic_error("graph already contains a node with such id");
    }

    this->_nodes.emplace_back(node_id);
}

void Graph::add_edge(int source_node_id, int destination_node_id, int weight) {
    if (std::any_of(this->_edges.begin(), this->_edges.end(),
                    [&](const Edge &other){
                        return other.source().id() == source_node_id
                               && other.destination().id() == destination_node_id;
                    })) {
        throw std::logic_error("graph already contains an edge between these nodes");
    }

    auto source_it = find_node_with_id(this->_nodes, source_node_id);
    if (source_it == this->_nodes.end()) {
        throw std::logic_error("source node does not exist");
    }

    auto destination_it = find_node_with_id(this->_nodes, destination_node_id);
    if (destination_it == this->_nodes.end()) {
        throw std::logic_error("destination node does not exist");
    }

    Node &source = *source_it;
    Node &destination = *destination_it;

    Edge new_edge{source, destination, weight};

    source._add_edge(new_edge);
    destination._add_edge(new_edge);

    this->_edges.push_back(new_edge);
}

void Graph::remove_node(int node_id) {
    auto it = find_node_with_id(this->_nodes, node_id);
    if (it == this->_nodes.end()) {
        throw std::logic_error("no node with given id was found");
    }

    Node &to_be_removed = *it;
    for (const Edge &e : to_be_removed.ingoing_edges()) {
        this->remove_edge(e.source().id(), e.destination().id());
    }
    for (const Edge &e : to_be_removed.outgoing_edges()) {
        this->remove_edge(e.source().id(), e.destination().id());
    }

    /**
     * When deleting a node from the vector - all the refs pointing to it will be now pointing to the previous element.
     * This will do as a workaround.
     */
    *it = Node(DELETED);
}

void Graph::remove_edge(int source_node_id, int destination_node_id) {
    auto it = std::find_if(this->_edges.begin(), this->_edges.end(),
                           [&](const Edge &e){
                               return e.source().id() == source_node_id
                                      && e.destination().id() == destination_node_id;
                           });

    if (it == this->_edges.end()) {
        throw std::logic_error("no edge between given nodes was found");
    }

    const Edge &to_be_removed = *it;
    to_be_removed.source()._remove_edge(to_be_removed);
    to_be_removed.destination()._remove_edge(to_be_removed);

    this->_edges.erase(it);
}

static std::vector<Node>::iterator find_node_with_id(std::vector<Node> &nodes, int node_id) {
    return std::find_if(nodes.begin(), nodes.end(), [&](const Node &node){
        return node.id() == node_id;
    });
}