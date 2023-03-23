#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int makeConnected(int n, std::vector<std::vector<int>> const &connections) const
    {
        std::vector<std::vector<size_t>> nodes(n, std::vector<size_t>());
        for (std::vector<int> const &connection : connections)
        {
            const int a = connection[0];
            const int b = connection[1];
            nodes[a].push_back(b);
            nodes[b].push_back(a);
        }
        std::vector<bool> visited(n, false);
        size_t componentsCount = 0;
        size_t extraConnectionsCount = 0;
        for (size_t node = 0; node < nodes.size(); ++node)
        {
            if (!visited[node])
            {
                ++componentsCount;
                extraConnectionsCount += processComponent(nodes, visited, node);
            }
        }
        if (componentsCount == 1)
            return 0;
        return extraConnectionsCount < (componentsCount - 1) ? -1 : static_cast<int>(componentsCount - 1);
    }

private:
    [[nodiscard]] size_t processComponent(std::vector<std::vector<size_t>> const &nodes, std::vector<bool> &visited, size_t start) const
    {
        size_t extraConnectionsCount = 0;
        std::queue<std::pair<size_t, size_t>> nodesQueue;
        nodesQueue.emplace(start, nodes.size());
        visited[start] = true;
        while (!nodesQueue.empty())
        {
            auto [node, parent] = nodesQueue.front();
            nodesQueue.pop();
            for (size_t neighbor : nodes[node])
            {
                if (neighbor == parent)
                    continue;
                if (visited[neighbor])
                    ++extraConnectionsCount;
                else
                {
                    visited[neighbor] = true;
                    nodesQueue.emplace(neighbor, node);
                }
            }
        }
        return extraConnectionsCount / 2;
    }
};

}

namespace NumberOperationsMakeNetworkConnectedTask
{

TEST(NumberOperationsMakeNetworkConnectedTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.makeConnected(4, {{0, 1}, {0, 2}, {1, 2}}));
    ASSERT_EQ(2, solution.makeConnected(6, {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}}));
    ASSERT_EQ(-1, solution.makeConnected(6, {{0, 1}, {0, 2}, {0, 3}, {1, 2}}));
}

}