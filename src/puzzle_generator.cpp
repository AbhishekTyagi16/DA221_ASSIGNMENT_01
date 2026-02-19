#include <iostream>
#include "puzzle_generator.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
using namespace std;
vector<vector<int>> generate_puzzle()
{
    vector<int> numbers(9, 0);
    iota(numbers.begin(), numbers.end(), 0);
    random_device rd;
    mt19937 g(rd());
    shuffle(numbers.begin(), numbers.end(), g);
    vector<vector<int>> puzzle(3, vector<int>(3));
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            puzzle[i][j] = numbers[3 * i + j];
        }
    }
    return puzzle;
}