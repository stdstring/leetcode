#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int assignEdgeWeights(std::vector<std::vector<int>> const &edges) const
    {
        const size_t nodesCount = edges.size() + 1;
        std::vector<std::vector<int>> nodes(nodesCount);
        for (std::vector<int> const &edge : edges)
        {
            const int node1 = edge[0] - 1;
            const int node2 = edge[1] - 1;
            nodes[node1].emplace_back(node2);
            nodes[node2].emplace_back(node1);
        }
        const int maxDepth = calcMaxDepth(nodes, 0, -1);
        constexpr int modValue = 1000000007;
        int result = 1;
        for (int step = 0; step < maxDepth - 1; ++step)
            result = (2 * result) % modValue;
        return result;
    }

private:
    [[nodiscard]] int calcMaxDepth(std::vector<std::vector<int>> const &nodes, int current, int parent) const
    {
        int result = 0;
        for (const int next : nodes[current])
        {
            if (next == parent)
                continue;
            result = std::max(result, 1 + calcMaxDepth(nodes, next, current));
        }
        return result;
    }
};

}

namespace NumberWaysAssignEdgeWeights1Task
{

TEST(NumberWaysAssignEdgeWeights1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.assignEdgeWeights({{1, 2}}));
    ASSERT_EQ(2, solution.assignEdgeWeights({{1, 2}, {1, 3}, {3, 4}, {3, 5}}));
}

TEST(NumberWaysAssignEdgeWeights1TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.assignEdgeWeights({{1, 2}, {2, 3}, {4, 5}, {3, 4}}));
}

}
