#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> eventualSafeNodes(std::vector<std::vector<int>> const &graph) const
    {
        const int nodeCount = static_cast<int>(graph.size());
        // reversed graph + incoming links count
        std::vector<std::vector<int>> reversedGraph(nodeCount, std::vector<int>());
        std::vector<int> incomingLinkCounts(nodeCount, 0);
        for (int node = 0; node < nodeCount; ++node)
        {
            for (const int neighbor : graph[node])
            {
                reversedGraph[neighbor].emplace_back(node);
                ++incomingLinkCounts[node];
            }
        }
        // collect safe nodes
        std::vector<int> safeNodes;
        std::queue<int> queue;
        for (int node = 0; node < nodeCount; ++node)
        {
            if (incomingLinkCounts[node] == 0)
                queue.emplace(node);
        }
        while (!queue.empty())
        {
            int current = queue.front();
            queue.pop();
            safeNodes.emplace_back(current);
            for (const int neighbor : reversedGraph[current])
            {
                --incomingLinkCounts[neighbor];
                if (incomingLinkCounts[neighbor] == 0)
                    queue.emplace(neighbor);
            }
        }
        std::ranges::sort(safeNodes);
        return safeNodes;
    }
};

}

namespace FindEventualSafeStatesTask
{

TEST(FindEventualSafeStatesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 4, 5, 6}), solution.eventualSafeNodes({{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}}));
    ASSERT_EQ(std::vector<int>({4}), solution.eventualSafeNodes({{1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {}}));
}

TEST(FindEventualSafeStatesTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({4}), solution.eventualSafeNodes({{0}, {2, 3, 4}, {3, 4}, {0, 4}, {}}));
}

}