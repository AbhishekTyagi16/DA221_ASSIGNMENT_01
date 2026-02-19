#include "puzzle_state.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
using namespace std;

bool puzzle_state::operator==(const puzzle_state &other) const
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i] != other.board[i])
            return false;
    }
    return true;
}

bool puzzle_state::operator!=(const puzzle_state &other) const
{
    return !(*this == other);
}

int puzzle_state::blank_index() const
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 0)
            return i;
    }
    throw runtime_error("Blank (0) not found!");
}

bool puzzle_state::is_goal(const puzzle_state &goal) const
{
    return (*this == goal);
}

vector<pair<puzzle_state, string>> puzzle_state::neighbors() const
{
    vector<pair<puzzle_state, string>> out;
    int b = blank_index();
    int r = b / 3;
    int c = b % 3;
    if (r > 0)
    {
        puzzle_state nxt = *this;
        swap(nxt.board[b], nxt.board[b - 3]);
        out.push_back({nxt, "U"});
    }
    if (r < 2)
    {
        puzzle_state nxt = *this;
        swap(nxt.board[b], nxt.board[b + 3]);
        out.push_back({nxt, "D"});
    }
    if (c > 0)
    {
        puzzle_state nxt = *this;
        swap(nxt.board[b], nxt.board[b - 1]);
        out.push_back({nxt, "L"});
    }
    if (c < 2)
    {
        puzzle_state nxt = *this;
        swap(nxt.board[b], nxt.board[b + 1]);
        out.push_back({nxt, "R"});
    }
    return out;
}

string puzzle_state::pretty() const
{
    ostringstream oss;
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 0)
            oss << "_";
        else
            oss << int(board[i]);

        if (i % 3 == 2)
            oss << "\n";
        else
            oss << " ";
    }
    return oss.str();
}

size_t puzzle_state_hash::operator()(const puzzle_state &s) const noexcept
{
    size_t h = 0;
    for (int i = 0; i < 9; i++)
    {
        h = h * 10 + s.board[i];
    }
    return h;
}