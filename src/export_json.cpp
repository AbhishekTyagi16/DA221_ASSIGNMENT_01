#include "export_json.h"
#include <fstream>
#include <iostream>
static void json_write_string(std::ostream& os, const std::string& s) {
    os << '"';
    for (char c : s) {
        if (c == '\\' || c == '"') os << '\\' << c;
        else if (c == '\n') os << "\\n";
        else os << c;
    }
    os << '"';
}
bool export_solution_json(const astar_result& r, const std::string& filename) {
    if (!r.success || r.path_states.empty()) return false;
    std::ofstream out(filename);
    if (!out) return false;
    out << "{\n";
    out << "  \"moves\": [";
    for (int i = 0; i < (int)r.moves.size(); i++) {
        if (i) out << ", ";
        json_write_string(out, r.moves[i]);
    }
    out << "],\n";
    out << "  \"states\": [\n";
    for (int si = 0; si < (int)r.path_states.size(); si++) {
        out << "    [";
        for (int i = 0; i < 9; i++) {
            if (i) out << ", ";
            out << r.path_states[si].board[i];
        }
        out << "]";
        if (si + 1 < (int)r.path_states.size()) out << ",";
        out << "\n";
    }
    out << "  ]\n";
    out << "}\n";
    return true;
}
