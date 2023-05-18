#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findSmallestSetOfVertices(int n, std::vector<std::vector<int>> const &edges) const
    {
        std::vector<bool> nodesWithInputEdges(n, false);
        for (std::vector<int> const& edge : edges)
            nodesWithInputEdges[edge[1]] = true;
        std::vector<int> result;
        for (int node = 0; node < n; ++node)
        {
            if (!nodesWithInputEdges[node])
                result.emplace_back(node);
        }
        return result;
    }
};

}

namespace MinVerticesToReachAllNodesTask
{

TEST(MinVerticesToReachAllNodesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 3}), solution.findSmallestSetOfVertices(6, {{0, 1}, {0, 2}, {2, 5}, {3, 4}, {4, 2}}));
    ASSERT_EQ(std::vector<int>({0, 2, 3}), solution.findSmallestSetOfVertices(5, {{0, 1}, {2, 1}, {3, 1}, {1, 4}, {2, 4}}));
}

}