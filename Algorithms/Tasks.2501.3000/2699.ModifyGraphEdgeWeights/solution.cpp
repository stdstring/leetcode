#include <queue>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> modifiedGraphEdges(int n, std::vector<std::vector<int>> const &edges, int source, int destination, int target) const
    {
        auto [graph, specialEdges] = buildGraph(n, edges, target);
        int initShortestDistance = findShortestPath(n, graph, source, destination);
        if (initShortestDistance < target)
            return {};
        if (initShortestDistance == target)
            return extractEdges(n, graph);
        for (auto const &[nodeA, nodeB] : specialEdges)
        {
            graph[nodeA][nodeB] = 1;
            graph[nodeB][nodeA] = 1;
            int shortestDistance = findShortestPath(n, graph, source, destination);
            if (shortestDistance <= target)
            {
                int distanceDelta = target - shortestDistance;
                graph[nodeA][nodeB] += distanceDelta;
                graph[nodeB][nodeA] += distanceDelta;
                return extractEdges(n, graph);
            }
        }
        return {};
    }

private:
    [[nodiscard]] std::pair<std::vector<std::unordered_map<int, int>>, std::vector<std::pair<int, int>>> buildGraph(int n, std::vector<std::vector<int>> const &edges, int target) const
    {
        std::vector<std::unordered_map<int, int>> graph(n);
        // nodeA, nodeB
        std::vector<std::pair<int, int>> specialEdges;
        for (std::vector<int> const& edge : edges)
        {
            int nodeA = edge[0];
            int nodeB = edge[1];
            int weight = edge[2];
            if (weight == -1)
            {
                specialEdges.emplace_back(nodeA, nodeB);
                weight = target + 1;
            }
            graph[nodeA].emplace(nodeB, weight);
            graph[nodeB].emplace(nodeA, weight);
        }
        return {graph, specialEdges};
    }

    [[nodiscard]] int findShortestPath(int n, std::vector<std::unordered_map<int, int>> const &graph, int source, int destination) const
    {
        std::vector<int> distances(n, INT_MAX);
        distances[source] = 0;
        // node, distance
        auto cmp = [](std::pair<int, int> const &l, std::pair<int, int> const &r){ return l.second > r.second; };
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> nodeQueue(cmp);
        nodeQueue.emplace(source, 0);
        while (!nodeQueue.empty())
        {
            auto [current, distance] = nodeQueue.top();
            nodeQueue.pop();
            if (current == destination)
                return distance;
            if (distances[current] < distance)
                continue;
            for (const auto &[neighbor, weight] : graph[current])
            {
                int neighborDistance = distance + weight;
                if (neighborDistance < distances[neighbor])
                {
                    distances[neighbor] = neighborDistance;
                    nodeQueue.emplace(neighbor, neighborDistance);
                }
            }
        }
        return INT_MAX;
    }

    [[nodiscard]] std::vector<std::vector<int>> extractEdges(int n, std::vector<std::unordered_map<int, int>> const &graph) const
    {
        std::vector<std::vector<int>> edges;
        for (int node = 0; node < n; ++node)
        {
            for (auto const &[neighbor, weight] : graph[node])
            {
                if (node < neighbor)
                    edges.emplace_back(std::vector<int>({node, neighbor, weight}));
            }
        }
        return edges;
    }
};

}

namespace ModifyGraphEdgeWeightsTask
{

TEST(ModifyGraphEdgeWeightsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 2, 1}, {0, 3, 1}, {1, 4, 1}, {3, 4, 3}}),
              solution.modifiedGraphEdges(5, {{4, 1, -1}, {2, 0, -1}, {0, 3, -1}, {4, 3, -1}}, 0, 1, 5));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.modifiedGraphEdges(3, {{0, 1, -1}, {0, 2, 5}}, 0, 2, 6));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 1, 4}, {0, 3, 1}, {1, 2, 3}, {2, 3, 5}}),
              solution.modifiedGraphEdges(4, {{1, 0, 4}, {1, 2, 3}, {2, 3, 5}, {0, 3, -1}}, 0, 2, 6));
}

TEST(ModifyGraphEdgeWeightsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    std::vector<std::vector<int>> edges({{0, 9, 950}, {4, 3, -1}, {4, 8, -1}, {4, 6, -1}, {9, 6, -1}, {9, 5, 516}, {5, 1, 365}, {2, 1, -1}, {2, 7, -1}, {10, 7, -1}, {4, 0, 682}});
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.modifiedGraphEdges(11, edges, 0, 1, 703310908));
}

}