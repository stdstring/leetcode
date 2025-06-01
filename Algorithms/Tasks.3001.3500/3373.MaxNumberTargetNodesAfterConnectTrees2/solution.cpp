#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> maxTargetNodes(std::vector<std::vector<int>> const &edges1, std::vector<std::vector<int>> const &edges2) const
    {
        std::vector<std::vector<int>> graph1(createGraph(edges1));
        std::vector<std::vector<int>> graph2(createGraph(edges2));
        int graph2BestResult = 0;
        if (graph2.size() > 1)
        {
            EvenOddCount graph2EvenOddCount(calcEvenOddNodesCount(graph2, 0, -1, 0));
            graph2BestResult = std::max(graph2EvenOddCount.EvenCount, graph2EvenOddCount.OddCount);
        }
        EvenOddCount graph1EvenOddCount(calcEvenOddNodesCount(graph1, 0, -1, 0));
        std::vector<EvenOddMark> evenOddMarks(graph1.size());
        markGraphEvenOddNodes(graph1, 0, -1, 0, evenOddMarks);
        std::vector<int> result(graph1.size());
        for (size_t node = 0; node < graph1.size(); ++node)
            result[node] = ((evenOddMarks[node] == EvenOddMark::Even) ? graph1EvenOddCount.EvenCount : graph1EvenOddCount.OddCount) + graph2BestResult;
        return result;
    }

private:
    struct EvenOddCount
    {
        int EvenCount = 0;
        int OddCount = 0;
    };

    enum class EvenOddMark { Even, Odd };

    [[nodiscard]] std::vector<std::vector<int>> createGraph(std::vector<std::vector<int>> const &edges) const
    {
        std::vector<std::vector<int>> graph(edges.size() + 1);
        for (std::vector<int> const &edge : edges)
        {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }
        return graph;
    }

    [[nodiscard]] EvenOddCount calcEvenOddNodesCount(std::vector<std::vector<int>> const &graph, int current, int parent, int length) const
    {
        EvenOddCount result;
        for (const int neighbor : graph[current])
        {
            if (neighbor == parent)
                continue;
            auto [evenCount, oddCount] = calcEvenOddNodesCount(graph, neighbor, current, length + 1);
            result.EvenCount += evenCount;
            result.OddCount += oddCount;
        }
        ++((length % 2) == 0 ? result.EvenCount : result.OddCount);
        return result;
    }

    void markGraphEvenOddNodes(std::vector<std::vector<int>> const &graph, int current, int parent, int length, std::vector<EvenOddMark> &evenOddMarks) const
    {
        evenOddMarks[current] = (length % 2) == 0 ? EvenOddMark::Even : EvenOddMark::Odd;
        for (int neighbor : graph[current])
        {
            if (neighbor == parent)
                continue;
            markGraphEvenOddNodes(graph, neighbor, current, length + 1, evenOddMarks);
        }
    }
};

}

namespace MaxNumberTargetNodesAfterConnectTrees2Task
{

TEST(MaxNumberTargetNodesAfterConnectTrees2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({8, 7, 7, 8, 8}),
              solution.maxTargetNodes({{0, 1}, {0, 2}, {2, 3}, {2, 4}}, {{0, 1}, {0, 2}, {0, 3}, {2, 7}, {1, 4}, {4, 5}, {4, 6}}));
    ASSERT_EQ(std::vector<int>({3, 6, 6, 6, 6}),
              solution.maxTargetNodes({{0, 1}, {0, 2}, {0, 3}, {0, 4}}, {{0, 1}, {1, 2}, {2, 3}} ));
}

}