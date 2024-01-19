#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countCompleteComponents(int n, std::vector<std::vector<int>> const &edges) const
    {
        std::vector<std::vector<int>> nodes(n);
        for (std::vector<int> const &edge : edges)
        {
            nodes[edge[0]].emplace_back(edge[1]);
            nodes[edge[1]].emplace_back(edge[0]);
        }
        std::vector<bool> visited(n, false);
        size_t completeComponentsCount = 0;
        for (int node = 0; node < n; ++node)
        {
            if (visited[node])
                continue;
            std::vector<int> connectedComponent(getConnectedComponent(nodes, visited, node));
            if (isConnectedComponentComplete(nodes, connectedComponent))
                ++completeComponentsCount;
        }
        return static_cast<int>(completeComponentsCount);
    }

private:
    [[nodiscard]] std::vector<int> getConnectedComponent(std::vector<std::vector<int>> const &nodes, std::vector<bool> &visited, int start) const
    {
        std::vector<int> connectedComponent;
        visited[start] = true;
        std::queue<int> nodesQueue;
        nodesQueue.emplace(start);
        while (!nodesQueue.empty())
        {
            int current = nodesQueue.front();
            nodesQueue.pop();
            connectedComponent.emplace_back(current);
            for (const int neighbor : nodes[current])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    nodesQueue.emplace(neighbor);
                }
            }
        }
        return connectedComponent;
    }

    [[nodiscard]] bool isConnectedComponentComplete(std::vector<std::vector<int>> const &nodes, std::vector<int> const &connectedComponent) const
    {
        const size_t nodeCount = connectedComponent.size();
        const size_t connectionCount = nodeCount - 1;
        return std::ranges::all_of(connectedComponent, [&nodes, connectionCount](int node) { return nodes[node].size() == connectionCount; });
    }
};

}

namespace CountNumberOfCompleteComponentsTask
{

TEST(CountNumberOfCompleteComponentsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.countCompleteComponents(6, {{0, 1}, {0, 2}, {1, 2}, {3, 4}}));
    ASSERT_EQ(1, solution.countCompleteComponents(6, {{0, 1}, {0, 2}, {1, 2}, {3, 4}, {3, 5}}));
}

}