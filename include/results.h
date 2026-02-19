#pragma once
#include "astar.h"
#include <string>
#include <vector>
struct run_row {
    int instance_id;
    std::string heuristic_name;
    astar_metrics m;
};
void print_results_table(const std::vector<run_row>& rows);
