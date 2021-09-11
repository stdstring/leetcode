#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct PathData
{
    PathData() : PathCount(0), TotalPath(0)
    {
    }

    size_t PathCount;
    size_t TotalPath;
};

class Solution
{
public:
    std::vector<int> sumOfDistancesInTree(int n, std::vector<std::vector<int>> const &edges) const
    {
        const size_t nodesCount = n;
        // create graph
        std::vector<std::vector<size_t>> graph(nodesCount);
        for (std::vector<int> const &edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        // fill path data
        std::vector<PathData> pathsData(nodesCount);
        generatePathsData(graph, 0, nodesCount, pathsData);
        // calc path to each node
        std::vector<int> result(nodesCount, 0);
        result[0] = static_cast<int>(pathsData[0].TotalPath);
        std::queue<size_t> nodes;
        nodes.push(0);
        while (!nodes.empty())
        {
            const size_t current = nodes.front();
            for (size_t edge : graph[current])
            {
                if (result[edge] != 0)
                    continue;
                const size_t currentWithoutEdgePathCount = pathsData[current].PathCount - (pathsData[edge].PathCount + 1);
                const size_t currentWithoutEdgeTotalPath = pathsData[current].TotalPath - (pathsData[edge].TotalPath + pathsData[edge].PathCount + 1);
                pathsData[edge].PathCount += (currentWithoutEdgePathCount + 1);
                pathsData[edge].TotalPath += (currentWithoutEdgeTotalPath + currentWithoutEdgePathCount + 1);
                result[edge] = static_cast<int>(pathsData[edge].TotalPath);
                nodes.push(edge);
            }
            nodes.pop();
        }
        return result;
    }

private:
    void generatePathsData(std::vector<std::vector<size_t >> const &graph, size_t  current, size_t  parent, std::vector<PathData> &pathsData) const
    {
        for (size_t edge : graph[current])
        {
            if (edge == parent)
                continue;
            generatePathsData(graph, edge, current, pathsData);
            pathsData[current].PathCount += (pathsData[edge].PathCount + 1);
            pathsData[current].TotalPath += (pathsData[edge].TotalPath + pathsData[edge].PathCount + 1);
        }
    }
};

}

namespace SumOfDistancesInTreeTask
{

TEST(SumOfDistancesInTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({8, 12, 6, 10, 10, 10}), solution.sumOfDistancesInTree(6, {{0, 1}, {0, 2}, {2, 3}, {2, 4}, {2, 5}}));
    ASSERT_EQ(std::vector<int>({0}), solution.sumOfDistancesInTree(1, {}));
    ASSERT_EQ(std::vector<int>({1, 1}), solution.sumOfDistancesInTree(2, {{1, 0}}));
}

}