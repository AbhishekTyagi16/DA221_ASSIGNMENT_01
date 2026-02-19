#include "instances.h"
#include "check_solvable.h"
#include <set>
#include <string>
using namespace std;
vector<vector<int>> generate_puzzle(); 
static puzzle_state grid_to_state(const vector<vector<int>>& g) {
    vector<int> b(9);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            b[3*i + j] = g[i][j];
        }
    }
    return puzzle_state(b);
}
static string key_from_grid(const vector<vector<int>>& g) {
    string k;
    k.reserve(9);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            k.push_back(char('0' + g[i][j])); 
    return k;
}
vector<vector<int>> default_goal_grid() {
    return {
        {1,2,3},
        {4,5,6},
        {7,8,0}
    };
}
puzzle_state default_goal_state() {
    return puzzle_state({1,2,3,4,5,6,7,8,0});
}
vector<puzzle_state> generate_instances(int n) {
    vector<puzzle_state> out;
    out.reserve(n);
    auto goalG = default_goal_grid();
    set<string> seen; 
    while ((int)out.size() < n) {
        auto g = generate_puzzle();
        if (!isSolvable(g, goalG)) continue;
        string k = key_from_grid(g);
        if (seen.count(k)) continue;

        seen.insert(k);
        out.push_back(grid_to_state(g));
    }
    return out;
}
