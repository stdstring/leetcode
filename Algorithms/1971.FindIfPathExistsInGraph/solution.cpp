#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool validPath(int n, std::vector<std::vector<int>> const &edges, int source, int destination) const
    {
        if (source == destination)
            return true;
        std::vector<std::vector<int>> graph(n, std::vector<int>());
        for (std::vector<int> const &edge : edges)
        {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }
        std::vector<bool> visited(n, false);
        std::queue<int> queue;
        visited[source] = true;
        queue.push(source);
        while (!queue.empty())
        {
            const int current = queue.front();
            queue.pop();
            for (int neighbor : graph[current])
            {
                if (neighbor == destination)
                    return true;
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
        return false;
    }
};

}

namespace FindIfPathExistsInGraphTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.validPath(3, {{0, 1}, {1, 2}, {2, 0}}, 0, 2));
    ASSERT_EQ(false, solution.validPath(6, {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}}, 0, 5));
}

}