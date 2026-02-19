#include "astar.h"
#include <queue>
#include <unordered_map>
#include <chrono>
#include <algorithm>

using namespace std;
struct node
{
    puzzle_state s;
    int g = 0;
    int f = 0;
};
struct node_cmp
{
    bool operator()(const node &a, const node &b) const
    {
        if (a.f != b.f)
            return a.f > b.f;
        return a.g < b.g;
    }
};
static void reconstruct_path(
    const puzzle_state &start,
    const puzzle_state &goal,
    const unordered_map<puzzle_state, pair<puzzle_state, string>, puzzle_state_hash> &parent,
    vector<puzzle_state> &out_states,
    vector<string> &out_moves)
{
    vector<puzzle_state> st_rev;
    vector<string> mv_rev;
    puzzle_state cur = goal;
    st_rev.push_back(cur);
    while (!(cur == start))
    {
        auto it = parent.find(cur);
        if (it == parent.end())
            break;
        mv_rev.push_back(it->second.second);
        cur = it->second.first;
        st_rev.push_back(cur);
    }
    reverse(st_rev.begin(), st_rev.end());
    reverse(mv_rev.begin(), mv_rev.end());
    out_states = move(st_rev);
    out_moves = move(mv_rev);
}
astar_result astar(const puzzle_state &start,
                   const puzzle_state &goal,
                   heuristic_fn h)
{
    astar_result res;
    auto t0 = chrono::high_resolution_clock::now();
    priority_queue<node, vector<node>, node_cmp> pq;
    unordered_map<puzzle_state, int, puzzle_state_hash> best_g;
    unordered_map<puzzle_state, pair<puzzle_state, string>, puzzle_state_hash> parent;
    pq.push({start, 0, 0 + h(start)});
    best_g[start] = 0;
    while (!pq.empty())
    {
        res.metrics.max_frontier = max(res.metrics.max_frontier, pq.size());
        node cur = pq.top();
        pq.pop();
        res.metrics.nodes_popped++;
        auto itg = best_g.find(cur.s);
        if (itg == best_g.end() || itg->second != cur.g)
            continue;
        if (cur.s == goal)
        {
            res.success = true;
            reconstruct_path(start, goal, parent, res.path_states, res.moves);
            res.metrics.solution_length = (int)res.moves.size();
            break;
        }
        res.metrics.nodes_expanded++;
        for (auto &pr : cur.s.neighbors())
        {
            const puzzle_state &nxt = pr.first;
            const string &mv = pr.second;
            int ng = cur.g + 1;
            auto it = best_g.find(nxt);
            if (it == best_g.end() || ng < it->second)
            {
                best_g[nxt] = ng;
                parent[nxt] = {cur.s, mv};
                int nf = ng + h(nxt);
                pq.push({nxt, ng, nf});
            }
        }
    }
    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double> dt = t1 - t0;
    res.metrics.runtime_sec = dt.count();
    return res;
}
