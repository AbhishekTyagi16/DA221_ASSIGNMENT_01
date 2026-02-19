#pragma once
#include "astar.h"
#include <string>
bool export_solution_json(const astar_result& r, const std::string& filename);
