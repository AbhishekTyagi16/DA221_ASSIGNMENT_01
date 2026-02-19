#include "check_solvable.h"
#include <vector>
using namespace std;

static int countInversions(const vector<int> &v)
{
    int inv = 0;
    for (int i = 0; i < 9; i++)
    {
        if (v[i] == 0)
            continue;
        for (int j = i + 1; j < 9; j++)
        {
            if (v[j] == 0)
                continue;
            if (v[i] > v[j])
                inv++;
        }
    }
    return inv;
}
bool isSolvable(const vector<vector<int>> &startState,
                const vector<vector<int>> &goalState)
{
    vector<int> v1(9), v2(9);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            v1[3 * i + j] = startState[i][j];
            v2[3 * i + j] = goalState[i][j];
        }
    }
    int inv1 = countInversions(v1);
    int inv2 = countInversions(v2);
    return (inv1 % 2) == (inv2 % 2);
}
