#include "results.h"
#include <iostream>
#include <iomanip>
using namespace std;
void print_results_table(const vector<run_row> &rows)
{
    cout << "\n=== SUMMARY ===\n";
    cout << left
         << setw(8) << "Inst"
         << setw(12) << "Heuristic"
         << setw(12) << "Time(ms)"
         << setw(10) << "SolLen"
         << setw(12) << "Popped"
         << setw(12) << "Expanded"
         << "\n";
    cout << string(8 + 12 + 12 + 10 + 12 + 12, '-') << "\n";
    for (auto &r : rows)
    {
        cout << left
             << setw(8) << r.instance_id
             << setw(12) << r.heuristic_name
             << setw(12) << fixed << setprecision(3) << (r.m.runtime_sec * 1000.0)
             << setw(10) << r.m.solution_length
             << setw(12) << r.m.nodes_popped
             << setw(12) << r.m.nodes_expanded
             << "\n";
    }
}