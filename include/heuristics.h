#pragma once
#include "puzzle_state.h"
struct goal_positions
{
    int pos[9];
};
goal_positions build_goal_positions(const puzzle_state &goal);
int h_misplaced(const puzzle_state &s, const puzzle_state &goal);
int h_manhattan(const puzzle_state &s, const goal_positions &gp);
int h_custom(const puzzle_state &s, const goal_positions &gp);