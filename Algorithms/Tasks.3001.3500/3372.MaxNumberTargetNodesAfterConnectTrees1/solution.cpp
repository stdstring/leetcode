#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> maxTargetNodes(std::vector<std::vector<int>> const &edges1, std::vector<std::vector<int>> const &edges2, int k) const
    {
        std::vector<std::vector<int>> graph1(createGraph(edges1));
        std::vector<std::vector<int>> graph2(createGraph(edges2));
        const int n = static_cast<int>(graph1.size());
        const int m = static_cast<int>(graph2.size());
        int bestCount2 = 0;
        for (int node = 0; node < m; ++node)
            bestCount2 = std::max(bestCount2, countNearestNodes(graph2, node, -1, 0, k - 1));
        std::vector<int> result(n);
        for (int node = 0; node < n; ++node)
            result[node] = countNearestNodes(graph1, node, -1, 0, k) + bestCount2;
        return result;
    }

private:
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

    [[nodiscard]] int countNearestNodes(std::vector<std::vector<int>> const &graph, int start, int parent, int length, int lengthLimit) const
    {
        if (length > lengthLimit)
            return 0;
        int result = 1;
        for (int neighbor : graph[start])
        {
            if (neighbor == parent)
                continue;
            result += countNearestNodes(graph, neighbor, start, length + 1, lengthLimit);
        }
        return result;
    }
};

}

namespace SomeLeetcodeTaskTask
{

TEST(SomeLeetcodeTaskTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({9, 7, 9, 8, 8}),
              solution.maxTargetNodes({{0, 1}, {0, 2}, {2, 3}, {2, 4}}, {{0, 1}, {0, 2}, {0, 3}, {2, 7}, {1, 4}, {4, 5}, {4, 6}}, 2));
    ASSERT_EQ(std::vector<int>({6, 3, 3, 3, 3}),
              solution.maxTargetNodes({{0, 1}, {0, 2}, {0, 3}, {0, 4}}, {{0, 1}, {1, 2}, {2, 3}}, 1));
}

}