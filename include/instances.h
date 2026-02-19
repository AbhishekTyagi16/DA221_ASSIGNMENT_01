#pragma once
#include "puzzle_state.h"
#include <vector>
puzzle_state default_goal_state();
std::vector<std::vector<int>> default_goal_grid();
std::vector<puzzle_state> generate_instances(int n);
