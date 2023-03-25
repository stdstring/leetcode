#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long countPairs(int n, std::vector<std::vector<int>> const &edges) const
    {
        std::vector<std::vector<size_t>> nodes(n, std::vector<size_t>());
        for (std::vector<int> const &edge : edges)
        {
            size_t a = edge[0];
            size_t b = edge[1];
            nodes[a].emplace_back(b);
            nodes[b].emplace_back(a);
        }
        std::vector<bool> visited(n, false);
        long long result = 0;
        size_t processedNodes = 0;
        for (size_t node = 0; node < nodes.size(); ++node)
        {
            if (!visited[node])
            {
                const size_t componentSize = processComponent(nodes, node, visited);
                result += static_cast<long long>(processedNodes * componentSize);
                processedNodes += componentSize;
            }
        }
        return result;
    }

private:
    [[nodiscard]] size_t processComponent(std::vector<std::vector<size_t>> const &nodes, size_t start, std::vector<bool> &visited) const
    {
        size_t componentSize = 1;
        std::queue<size_t> componentQueue;
        componentQueue.emplace(start);
        visited[start] = true;
        while (!componentQueue.empty())
        {
            const size_t node = componentQueue.front();
            componentQueue.pop();
            for (const size_t neighbor : nodes[node])
            {
                if (!visited[neighbor])
                {
                    componentQueue.emplace(neighbor);
                    visited[neighbor] = true;
                    ++componentSize;
                }
            }
        }
        return componentSize;
    }
};

}

namespace CountUnreachableNodesPairsInGraphTask
{

TEST(CountUnreachableNodesPairsInGraphTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.countPairs(3, {{0, 1}, {0, 2}, {1, 2}}));
    ASSERT_EQ(14, solution.countPairs(7, {{0, 2}, {0, 5}, {2, 4}, {1, 6}, {5, 4}}));
}

TEST(CountUnreachableNodesPairsInGraphTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(4999950000, solution.countPairs(100000, {}));
}

}