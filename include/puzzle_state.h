#pragma once
#include <vector>
#include <string>
#include <utility>
#include <cstddef>
using namespace std;
struct puzzle_state
{
    vector<int> board;
    puzzle_state() : board(9, 0) {}
    puzzle_state(std::vector<int> b) : board(b) {}
    bool operator==(const puzzle_state &other) const;
    bool operator!=(const puzzle_state &other) const;
    int blank_index() const;
    bool is_goal(const puzzle_state &goal) const;
    vector<pair<puzzle_state, string>> neighbors() const;
    string pretty() const;
};
struct puzzle_state_hash
{
    size_t operator()(const puzzle_state &s) const noexcept;
};