#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minTime(int n, std::vector<std::vector<int>> const &edges, std::vector<bool> const &hasApple) const
    {
        std::vector<std::vector<int>> graph(n);
        for (std::vector<int> const &edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        return minTimeImpl(-1, 0, graph, hasApple);
    }

private:
    [[nodiscard]] int minTimeImpl(int parent, int current, std::vector<std::vector<int>> const &graph, std::vector<bool> const &hasApple) const
    {
        int result = 0;
        for (const int neighbor : graph[current])
        {
            if (neighbor == parent)
                continue;
            result += minTimeImpl(current, neighbor, graph, hasApple);
        }
        if ((hasApple[current] || result != 0) && (current != 0))
            result += 2;
        return result;
    }
};

}

namespace MinTimeToCollectAllApplesInTreeTask
{

TEST(MinTimeToCollectAllApplesInTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(8, solution.minTime(7, {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}}, {false, false, true, false, true, true, false}));
    ASSERT_EQ(6, solution.minTime(7, {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}}, {false, false, true, false, false, true, false}));
    ASSERT_EQ(0, solution.minTime(7, {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}}, {false, false, false, false, false, false, false}));
}

}