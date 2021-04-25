#ifndef MAXFLOW_STEPPER_CALCULATOR_H
#define MAXFLOW_STEPPER_CALCULATOR_H

#include <utility>
#include <vector>
#include <queue>

#include "graph.h"
#include "residual_graph.h"


struct MaxflowCalculationResults;

class MaxflowStepperCalculator {
public:
    MaxflowStepperCalculator(const Graph &graph, int source_id, int sink_id);

    bool finished();
    MaxflowCalculationResults do_step();
    int get_current_maximum_flow() const;

private:
    ResidualGraph _graph;
    int _maximum_flow_value;
    int _source_id;
    int _sink_id;
    std::vector<int> _prev;

    bool is_sink_reachable();
};

struct MaxflowCalculationResults {
    int maximum_flow_value;

    /* information about last augmented path */
    std::vector<int> augmented_path_nodes;
    int bottleneck_value;

    MaxflowCalculationResults(int _maxflow, int _bottleneck, std::vector<int> _aug_path)
            : maximum_flow_value(_maxflow), bottleneck_value(_bottleneck), augmented_path_nodes(std::move(_aug_path)) {}
};


#endif //MAXFLOW_STEPPER_CALCULATOR_H