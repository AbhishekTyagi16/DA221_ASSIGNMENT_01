#pragma once
#include "puzzle_state.h"
#include <functional>
#include <string>
#include <vector>
#include <cstddef>
struct astar_metrics
{
    double runtime_sec = 0.0;
    int solution_length = -1;
    size_t nodes_popped = 0;
    size_t nodes_expanded = 0;
    size_t max_frontier = 0;
};
struct astar_result
{
    bool success = false;
    vector<puzzle_state> path_states;
    vector<string> moves;
    astar_metrics metrics;
};
using heuristic_fn = function<int(const puzzle_state &)>;
astar_result astar(const puzzle_state &start,
                   const puzzle_state &goal,
                   heuristic_fn h);
