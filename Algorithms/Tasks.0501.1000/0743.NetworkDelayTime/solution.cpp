#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct Connection
{
    Connection(int dest, int weight) : Dest(dest), Weight(weight)
    {
    }

    int Dest;
    int Weight;
};

struct NodeData
{
    NodeData(int node, int totalCost) : Node(node), TotalCost(totalCost)
    {
    }

    int Node;
    int TotalCost;
};

class Solution
{
public:
    [[nodiscard]] int networkDelayTime(std::vector<std::vector<int>> const &times, int n, int k) const
    {
        std::vector<std::vector<Connection>> graph(n, std::vector<Connection>());
        for (std::vector<int> const &connection : times)
            graph[0LL + connection[0] - 1].emplace_back(connection[1], connection[2]);
        std::vector<bool> processedNodes(n, false);
        auto cmp = [](NodeData const &left, NodeData const &right){ return left.TotalCost > right.TotalCost; };
        std::priority_queue<NodeData, std::vector<NodeData>, decltype(cmp)> queue(cmp);
        int totalTimes = 0;
        size_t processedNodesCount = 0;
        queue.emplace(k, 0);
        while (!queue.empty())
        {
            const int currentNode = queue.top().Node;
            const int currentTime = queue.top().TotalCost;
            queue.pop();
            if (processedNodes[0LL + currentNode - 1])
                continue;
            processedNodes[0LL + currentNode - 1] = true;
            totalTimes = currentTime;
            ++processedNodesCount;
            for (Connection const &connection : graph[0LL + currentNode - 1])
            {
                if (processedNodes[0LL + connection.Dest - 1])
                    continue;
                queue.emplace(connection.Dest, currentTime + connection.Weight);
            }
        }
        return processedNodesCount < static_cast<size_t>(n) ? -1 : totalTimes;
    }
};

}

namespace NetworkDelayTimeTask
{

TEST(NetworkDelayTimeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.networkDelayTime({{2, 1, 1}, {2, 3, 1}, {3, 4, 1}}, 4, 2));
    ASSERT_EQ(1, solution.networkDelayTime({{1, 2, 1}}, 2, 1));
    ASSERT_EQ(-1, solution.networkDelayTime({{1, 2, 1}}, 2, 2));
}

}