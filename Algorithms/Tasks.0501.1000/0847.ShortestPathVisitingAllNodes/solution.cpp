#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct NodeData
{
    NodeData(int node, int bitmask) : Node(node), Bitmask(bitmask)
    {
    }

    int Node;
    int Bitmask;
};

class Solution
{
public:
    [[nodiscard]] int shortestPathLength(std::vector<std::vector<int>> const &graph) const
    {
        // Dijkstra approach
        const size_t nodeCount = graph.size();
        const size_t combinationCount = 1LL << nodeCount;
        std::vector<std::vector<int>> cost(nodeCount, std::vector<int>(combinationCount, INT_MAX));
        auto cmp = [&cost](NodeData const &left, NodeData const &right) { return cost[left.Node][left.Bitmask] < cost[right.Node][right.Bitmask]; };
        std::priority_queue<NodeData, std::vector<NodeData>, decltype(cmp)> queue(cmp);
        for (size_t node = 0; node < nodeCount; ++node)
        {
            int mask = 1 << node;
            cost[node][mask] = 0;
            queue.emplace(node, mask);
        }
        while (!queue.empty())
        {
            const int current = queue.top().Node;
            const int currentMask = queue.top().Bitmask;
            queue.pop();
            for (int child : graph[current])
            {
                int childMask = currentMask | (1 << child);
                if (cost[child][childMask] > cost[current][currentMask] + 1)
                {
                    cost[child][childMask] = cost[current][currentMask] + 1;
                    queue.emplace(child, childMask);
                }
            }
        }
        const size_t totalMask = 0LL + combinationCount - 1;
        int length = INT_MAX;
        for (size_t node = 0; node < nodeCount; ++node)
            length = std::min(length, cost[node][totalMask]);
        return length;
    }
};

}

namespace ShortestPathVisitingAllNodesTask
{

TEST(ShortestPathVisitingAllNodesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.shortestPathLength({{1, 2, 3}, {0}, {0}, {0}}));
    ASSERT_EQ(4, solution.shortestPathLength({{1}, {0, 2, 4}, {1, 3, 4}, {2}, {1, 2}}));
}

}