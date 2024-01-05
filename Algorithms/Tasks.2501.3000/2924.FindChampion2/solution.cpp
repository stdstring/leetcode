#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findChampion(int n, std::vector<std::vector<int>> const &edges) const
    {
        std::vector<bool> nodesWithIncomingEdges(n, false);
        for (std::vector<int> const &edge : edges)
        {
            const int toNode = edge[1];
            nodesWithIncomingEdges[toNode] = true;
        }
        int champion = n;
        for (int team = 0; team < n; ++team)
        {
            if (nodesWithIncomingEdges[team])
                continue;
            if (champion != n)
                return -1;
            champion = team;
        }
        return champion;
    }
};

}

namespace FindChampion2Task
{

TEST(FindChampion2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.findChampion(3, {{0, 1}, {1, 2}}));
    ASSERT_EQ(-1, solution.findChampion(4, {{0, 2}, {1, 3}, {1, 2}}));
}

}