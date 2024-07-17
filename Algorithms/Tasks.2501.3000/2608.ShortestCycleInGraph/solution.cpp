#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findShortestCycle(int n, std::vector<std::vector<int>> const &edges) const
    {
        std::vector<std::vector<int>> graph(n);
        for (std::vector<int> const &edge : edges)
        {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }
        int shortestCycle = -1;
        for (int node = 0; node < n; ++node)
        {
            const int currentCycle = calcCycleSizeForStart(n, graph, node);
            if (currentCycle != -1)
                shortestCycle = std::min(shortestCycle == -1 ? INT_MAX : shortestCycle, currentCycle);
        }
        return shortestCycle;
    }

private:
    struct NodeData
    {
        NodeData(int current, int parent) : Current(current), Parent(parent)
        {
        }

        int Current;
        int Parent;
    };

    [[nodiscard]] int calcCycleSizeForStart(int n, std::vector<std::vector<int>> const &graph, int startNode) const
    {
        std::vector<int> visitSteps(n, -1);
        int step = 0;
        std::queue<NodeData> nodesQueue;
        nodesQueue.emplace(startNode, 0);
        visitSteps[startNode] = 0;
        while (!nodesQueue.empty())
        {
            ++step;
            const size_t currentPortion = nodesQueue.size();
            int minCycle = -1;
            for (size_t index = 0; index < currentPortion; ++index)
            {
                const NodeData data(nodesQueue.front());
                nodesQueue.pop();
                for (const int neighbor : graph[data.Current])
                {
                    if (neighbor == data.Parent)
                        continue;
                    if (visitSteps[neighbor] != -1)
                        minCycle = std::min(minCycle == -1 ? INT_MAX : minCycle, step + visitSteps[neighbor]);
                    visitSteps[neighbor] = step;
                    nodesQueue.emplace(neighbor, data.Current);
                }
            }
            if (minCycle != -1)
                return minCycle;
        }
        return -1;
    }
};

}

namespace ShortestCycleInGraphTask
{

TEST(ShortestCycleInGraphTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.findShortestCycle(7, {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5}, {5, 6}, {6, 3}}));
    ASSERT_EQ(-1, solution.findShortestCycle(4, {{0, 1}, {0, 2}}));
}

TEST(ShortestCycleInGraphTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.findShortestCycle(6, {{4, 1}, {5, 1}, {3, 2}, {5, 0}, {4, 0}, {3, 0}, {2, 1}}));
    ASSERT_EQ(3, solution.findShortestCycle(9, {{4, 5}, {1, 6}, {6, 4}, {5, 3}, {3, 6}, {0, 2}, {5, 8}, {0, 6}, {3, 0}, {6, 8}, {2, 8}, {1, 2}}));
}

}