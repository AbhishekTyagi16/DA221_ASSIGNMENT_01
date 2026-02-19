#include "heuristics.h"
#include <cstdlib>
#include <algorithm>

using namespace std;
goal_positions build_goal_positions(const puzzle_state &goal)
{
    goal_positions gp;
    for (int t = 0; t < 9; t++)
        gp.pos[t] = -1;
    for (int i = 0; i < 9; i++)
    {
        int tile = goal.board[i];
        gp.pos[tile] = i;
    }
    return gp;
}
int h_misplaced(const puzzle_state &s, const puzzle_state &goal)
{
    int cnt = 0;
    for (int i = 0; i < 9; i++)
    {
        if (s.board[i] == 0)
            continue;
        if (s.board[i] != goal.board[i])
            cnt++;
    }
    return cnt;
}
int h_manhattan(const puzzle_state &s, const goal_positions &gp)
{
    int dist = 0;
    for (int i = 0; i < 9; i++)
    {
        int tile = s.board[i];
        if (tile == 0)
            continue;
        int gi = gp.pos[tile];
        int r1 = i / 3, c1 = i % 3;
        int r2 = gi / 3, c2 = gi % 3;
        dist += abs(r1 - r2) + abs(c1 - c2);
    }
    return dist;
}
static int linear_conflict_row(const puzzle_state &s, const goal_positions &gp, int row)
{
    int conflict = 0;
    int goalCols[3];
    int k = 0;
    for (int col = 0; col < 3; col++)
    {
        int idx = row * 3 + col;
        int tile = s.board[idx];
        if (tile == 0)
            continue;
        int gidx = gp.pos[tile];
        int grow = gidx / 3;
        int gcol = gidx % 3;

        if (grow == row)
        {
            goalCols[k++] = gcol;
        }
    }
    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            if (goalCols[i] > goalCols[j])
                conflict++;
        }
    }
    return conflict;
}
static int linear_conflict_col(const puzzle_state &s, const goal_positions &gp, int col)
{
    int conflict = 0;
    int goalRows[3];
    int k = 0;

    for (int row = 0; row < 3; row++)
    {
        int idx = row * 3 + col;
        int tile = s.board[idx];
        if (tile == 0)
            continue;

        int gidx = gp.pos[tile];
        int grow = gidx / 3;
        int gcol = gidx % 3;

        if (gcol == col)
        {
            goalRows[k++] = grow;
        }
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            if (goalRows[i] > goalRows[j])
                conflict++;
        }
    }
    return conflict;
}
int h_custom(const puzzle_state &s, const goal_positions &gp)
{
    int man = h_manhattan(s, gp);
    int conflicts = 0;
    for (int r = 0; r < 3; r++)
        conflicts += linear_conflict_row(s, gp, r);
    for (int c = 0; c < 3; c++)
        conflicts += linear_conflict_col(s, gp, c);
    return man + 2 * conflicts;
}