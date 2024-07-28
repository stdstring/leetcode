#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int secondMinimum(int n, std::vector<std::vector<int>> const &edges, int time, int change) const
    {
        std::vector<std::vector<int>> graph(n);
        for (std::vector<int> const &edge : edges)
        {
            const int fromNode = edge[0] - 1;
            const int toNode = edge[1] - 1;
            graph[fromNode].emplace_back(toNode);
            graph[toNode].emplace_back(fromNode);
        }
        const std::vector<std::pair<int, int>> distances(calcDistances(n, graph, 0));
        const int secondResult = std::min(distances[n - 1].first + 2, distances[n - 1].second != INT_MAX ? distances[n - 1].second : distances[n - 1].first + 2);
        int totalTime = 0;
        for (int step = 0; step < secondResult; ++step)
        {
            if ((totalTime % (2 * change)) >= change)
                totalTime = ((totalTime / change) + 1) * change;
            totalTime += time;
        }
        return totalTime;
    }

private:
    struct Path
    {
        Path(int node, int distance) : Node(node), Distance(distance)
        {
        }
        int Node;
        int Distance;
    };

    [[nodiscard]] std::vector<std::pair<int, int>> calcDistances(int n, std::vector<std::vector<int>> const& graph, int start) const
    {
        std::vector<std::pair<int, int>> distances(n, std::pair<int, int>(INT_MAX, INT_MAX));
        distances[start] = std::pair<int, int>(0, 0);
        std::queue<Path> nodeQueue;
        nodeQueue.emplace(start, 0);
        while (!nodeQueue.empty())
        {
            const Path current(nodeQueue.front());
            nodeQueue.pop();
            const int nextDistance = current.Distance + 1;
            for (const int neighbor : graph[current.Node])
            {
                if (nextDistance < distances[neighbor].first)
                {
                    distances[neighbor].second = distances[neighbor].first;
                    distances[neighbor].first = nextDistance;
                    nodeQueue.emplace(neighbor, nextDistance);
                }
                else if ((distances[neighbor].first < nextDistance) && (nextDistance < distances[neighbor].second))
                {
                    distances[neighbor].second = nextDistance;
                    nodeQueue.emplace(neighbor, nextDistance);
                }
            }
        }
        return distances;
    }
};

}

namespace SecondMinTimeReachDestinationTask
{

TEST(SecondMinTimeReachDestinationTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.secondMinimum(5, {{1, 2}, {1, 3}, {1, 4}, {3, 4}, {4, 5}}, 3, 5));
    ASSERT_EQ(11, solution.secondMinimum(2, {{1, 2}}, 3, 2));
}

}