#include <iostream>
#include <vector>
#include <string>
#include "puzzle_state.h"
#include "heuristics.h"
#include "astar.h"
#include "instances.h"
#include "results.h"
#include "export_json.h" 
using namespace std;

static void print_solution_steps(const astar_result &r)
{
    if (!r.success)
    {
        cout << "No solution.\n";
        return;
    }

    cout << "Solution length = " << r.metrics.solution_length << "\n\n";
    cout << "Step 0:\n"
         << r.path_states[0].pretty() << "\n";

    for (int i = 0; i < (int)r.moves.size(); i++)
    {
        cout << "Move " << (i + 1) << ": " << r.moves[i] << "\n";
        cout << r.path_states[i + 1].pretty() << "\n";
    }
}

int main()
{
    puzzle_state goal = default_goal_state();
    goal_positions gp = build_goal_positions(goal);

    vector<puzzle_state> inst = generate_instances(10);

    vector<run_row> rows;
    rows.reserve(10 * 3);

    int samples_printed = 0;

    for (int i = 0; i < (int)inst.size(); i++)
    {
        cout << "\n=====================\n";
        cout << "Instance " << i << ":\n"
             << inst[i].pretty() << "\n";

        // Heuristic 1: misplaced
        auto h1 = [&](const puzzle_state &s)
        { return h_misplaced(s, goal); };
        astar_result r1 = astar(inst[i], goal, h1);
        rows.push_back({i, "misplaced", r1.metrics});

        // Heuristic 2: manhattan
        auto h2 = [&](const puzzle_state &s)
        { return h_manhattan(s, gp); };
        astar_result r2 = astar(inst[i], goal, h2);
        rows.push_back({i, "manhattan", r2.metrics});

        // Heuristic 3: custom
        auto h3 = [&](const puzzle_state &s)
        { return h_custom(s, gp); };
        astar_result r3 = astar(inst[i], goal, h3);
        rows.push_back({i, "custom", r3.metrics});
        if (samples_printed < 2 && r2.success && r2.metrics.solution_length >= 10)
        {
            cout << "\n=== SAMPLE SOLUTION " << (samples_printed + 1)
                 << " (Instance " << i << ", Manhattan) ===\n";

            print_solution_steps(r2);

            string fname = (samples_printed == 0) ? "sol_sample1.json" : "sol_sample2.json";
            if (export_solution_json(r2, fname))
            {
                cout << " Wrote " << fname << "\n";
                cout << "Open viewer.html and load " << fname << " to visualize.\n";
            }
            else
            {
                cout << "Failed to write " << fname << "\n";
            }
            samples_printed++;
        }
    }
    print_results_table(rows);
    if (samples_printed < 2)
    {
        cout << "\nNote: Only found " << samples_printed
             << " solutions with length >= 10.\n";
        cout << "If your assignment requires exactly 2, re-run (generator is random) "
             << "or adjust generator to create harder instances.\n";
    }
    return 0;
}
