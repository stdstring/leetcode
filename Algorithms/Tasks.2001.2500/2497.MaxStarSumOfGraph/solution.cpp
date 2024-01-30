#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxStarSum(std::vector<int> const &vals, std::vector<std::vector<int>> const &edges, int k) const
    {
        const size_t maxNeighbor = k;
        const size_t nodeCount = vals.size();
        std::vector<std::vector<int>> nodes(nodeCount);
        for (std::vector<int> const &edge : edges)
        {
            nodes[edge[0]].emplace_back(edge[1]);
            nodes[edge[1]].emplace_back(edge[0]);
        }
        int bestStarSum = INT_MIN;
        for (size_t node = 0; node < nodeCount; ++node)
        {
            int currentStarSum = vals[node];
            std::ranges::sort(nodes[node], [&vals](int l, int r) { return vals[l] > vals[r]; });
            for (size_t neighbor = 0; (neighbor < std::min(nodes[node].size(), maxNeighbor)) && (vals[nodes[node][neighbor]] > 0); ++neighbor)
                currentStarSum += vals[nodes[node][neighbor]];
            bestStarSum = std::max(bestStarSum, currentStarSum);
        }
        return bestStarSum;
    }
};

}

namespace MaxStarSumOfGraphTask
{

TEST(MaxStarSumOfGraphTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(16, solution.maxStarSum({1, 2, 3, 4, 10, -10, -20}, {{0, 1}, {1, 2}, {1, 3}, {3, 4}, {3, 5}, {3, 6}}, 2));
    ASSERT_EQ(-5, solution.maxStarSum({-5}, {}, 0));
}

TEST(MaxStarSumOfGraphTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(10, solution.maxStarSum({10, -1, -1}, {{0, 1}, {0, 2}}, 2));
}

}