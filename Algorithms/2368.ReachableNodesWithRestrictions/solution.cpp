#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int reachableNodes(int n, std::vector<std::vector<int>> const &edges, std::vector<int> const &restricted) const
    {
        std::vector<std::vector<int>> neighbors(n, std::vector<int>());
        for (std::vector<int> const &edge : edges)
        {
            neighbors[edge[0]].push_back(edge[1]);
            neighbors[edge[1]].push_back(edge[0]);
        }
        std::vector<bool> visited(n, false);
        for (const int restrictedNode : restricted)
            visited[restrictedNode] = true;
        if (visited[0])
            return 0;
        size_t visitedNodes = 0;
        std::queue<int> queue;
        queue.push(0);
        visited[0] = true;
        while (!queue.empty())
        {
            ++visitedNodes;
            for (int node : neighbors[queue.front()])
            {
                if (!visited[node])
                {
                    queue.push(node);
                    visited[node] = true;
                }
            }
            queue.pop();
        }
        return static_cast<int>(visitedNodes);
    }
};

}

namespace ReachableNodesWithRestrictionsTask
{

TEST(ReachableNodesWithRestrictionsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.reachableNodes(7, {{0, 1}, {1, 2}, {3, 1}, {4, 0}, {0, 5}, {5, 6}}, {4, 5}));
    ASSERT_EQ(3, solution.reachableNodes(7, {{0, 1}, {0, 2}, {0, 5}, {0, 4}, {3, 2}, {6, 5}}, {4, 2, 1}));
}

}
