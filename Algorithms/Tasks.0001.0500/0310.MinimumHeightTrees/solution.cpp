#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findMinHeightTrees(int n, std::vector<std::vector<int>> const &edges) const
    {
        if (n == 1)
            return {0};
        std::vector<std::vector<int>> nodes(n);
        for (std::vector<int> const &edge : edges)
        {
            nodes[edge[0]].push_back(edge[1]);
            nodes[edge[1]].push_back(edge[0]);
        }
        std::vector<size_t> degrees(n, 0);
        std::queue<int> nodesQueue;
        int unprocessedNodes = n;
        for (int node = 0; node < n; ++node)
        {
            degrees[node] = nodes[node].size();
            if (degrees[node] == 1)
            {
                nodesQueue.push(node);
                degrees[node] = 0;
            }
        }
        while (unprocessedNodes > 2)
        {
            const size_t queueSize = nodesQueue.size();
            for (size_t index = 0; index < queueSize; ++index)
            {
                const int current = nodesQueue.front();
                nodesQueue.pop();
                --unprocessedNodes;
                for (int neighbor : nodes[current])
                {
                    if (degrees[neighbor] > 1)
                        --degrees[neighbor];
                    if (degrees[neighbor] == 1)
                    {
                        nodesQueue.push(neighbor);
                        degrees[neighbor] = 0;
                    }
                }
            }
        }
        std::vector<int> roots;
        while (!nodesQueue.empty())
        {
            roots.push_back(nodesQueue.front());
            nodesQueue.pop();
        }
        return roots;
    }
};

}

namespace MinimumHeightTreesTask
{

TEST(MinimumHeightTreesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1}), solution.findMinHeightTrees(4, {{1, 0}, {1, 2}, {1, 3}}));
    ASSERT_EQ(std::vector<int>({3, 4}), solution.findMinHeightTrees(6, {{3, 0}, {3, 1}, {3, 2}, {3, 4}, {5, 4}}));
    ASSERT_EQ(std::vector<int>({0}), solution.findMinHeightTrees(1, {}));
    ASSERT_EQ(std::vector<int>({0, 1}), solution.findMinHeightTrees(2, {{0, 1}}));
}

TEST(MinimumHeightTreesTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({3}), solution.findMinHeightTrees(6, {{0, 1}, {0, 2}, {0, 3}, {3, 4}, {4, 5}}));
    ASSERT_EQ(std::vector<int>({1, 2}), solution.findMinHeightTrees(7, {{0, 1}, {1, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 6}}));
}

}