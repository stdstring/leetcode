#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countGoodNodes(std::vector<std::vector<int>> const &edges) const
    {
        const size_t nodesCount = edges.size() + 1;
        std::vector<std::vector<int>> graph(nodesCount);
        for (std::vector<int> const &edge : edges)
        {
            const int node1 = edge[0];
            const int node2 = edge[1];
            graph[node1].emplace_back(node2);
            graph[node2].emplace_back(node1);
        }
        return static_cast<int>(processTree(graph, 0, -1).GoodNodesCount);
    }

private:
    struct Result
    {
        Result(size_t nodesCount, size_t goodNodesCount) : NodesCount(nodesCount), GoodNodesCount(goodNodesCount)
        {
        }
        size_t NodesCount;
        size_t GoodNodesCount;
    };

    [[nodiscard]] Result processTree(std::vector<std::vector<int>> const &graph, int current, int parent) const
    {
        if ((graph[current].size() == 1) && (graph[current][0] == parent))
            return Result(1, 1);
        bool isCurrentNodeGood = true;
        const Result firstSubTreeResult(processTree(graph, graph[current][0] == parent ? graph[current][1] : graph[current][0], current));
        size_t nodesCount = 1 + firstSubTreeResult.NodesCount;
        size_t goodNodesCount = firstSubTreeResult.GoodNodesCount;
        for (size_t index = graph[current][0] == parent ? 2 : 1; index < graph[current].size(); ++index)
        {
            if (graph[current][index] == parent)
                continue;
            const Result subTreeResult(processTree(graph, graph[current][index], current));
            nodesCount += subTreeResult.NodesCount;
            goodNodesCount += subTreeResult.GoodNodesCount;
            if (firstSubTreeResult.NodesCount != subTreeResult.NodesCount)
                isCurrentNodeGood = false;
        }
        if (isCurrentNodeGood)
            ++goodNodesCount;
        return Result(nodesCount, goodNodesCount);
    }
};

}

namespace CountNumberGoodNodesTask
{

TEST(CountNumberGoodNodesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.countGoodNodes({{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}}));
    ASSERT_EQ(6, solution.countGoodNodes({{0, 1}, {1, 2}, {2, 3}, {3, 4}, {0, 5}, {1, 6}, {2, 7}, {3, 8}}));
    ASSERT_EQ(12, solution.countGoodNodes({{0, 1}, {1, 2}, {1, 3}, {1, 4}, {0, 5}, {5, 6}, {6, 7}, {7, 8}, {0, 9}, {9, 10}, {9, 12}, {10, 11}}));
}

TEST(CountNumberGoodNodesTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.countGoodNodes({{2, 0}, {4, 2}, {1, 2}, {3, 1}, {5, 1}}));
}

}