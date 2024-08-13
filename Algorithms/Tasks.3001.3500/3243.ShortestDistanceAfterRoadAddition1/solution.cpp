#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> shortestDistanceAfterQueries(int n, std::vector<std::vector<int>> const &queries) const
    {
        std::vector<std::vector<int>> graph(n);
        for (int node = 1; node < n; ++node)
            graph[node - 1].emplace_back(node);
        std::vector<int> answers(queries.size(), 0);
        for (size_t index = 0; index < queries.size(); ++index)
        {
            graph[queries[index][0]].emplace_back(queries[index][1]);
            answers[index] = calcDistance(graph);
        }
        return answers;
    }

private:
    [[nodiscard]] int calcDistance(std::vector<std::vector<int>> const &graph) const
    {
        const int destNode = static_cast<int>(graph.size() - 1);
        int distance = 0;
        std::vector<bool> visited(graph.size(), false);
        visited[0] = true;
        std::queue<int> nodeQueue;
        nodeQueue.emplace(0);
        while (!nodeQueue.empty())
        {
            const size_t portionSize = nodeQueue.size();
            for (size_t index = 0; index < portionSize; ++index)
            {
                const int current = nodeQueue.front();
                nodeQueue.pop();
                if (current == destNode)
                    return distance;
                for (const int neighbor : graph[current])
                {
                    if (!visited[neighbor])
                    {
                        visited[neighbor] = true;
                        nodeQueue.emplace(neighbor);
                    }
                }
            }
            ++distance;
        }
        return -1;
    }
};

}

namespace ShortestDistanceAfterRoadAddition1Task
{

TEST(ShortestDistanceAfterRoadAddition1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 2, 1}), solution.shortestDistanceAfterQueries(5, {{2, 4}, {0, 2}, {0, 4}}));
    ASSERT_EQ(std::vector<int>({1, 1}), solution.shortestDistanceAfterQueries(4, {{0, 3}, {0, 2}}));
}

TEST(ShortestDistanceAfterRoadAddition1TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({8, 6}), solution.shortestDistanceAfterQueries(14, {{0, 6}, {4, 12}}));
}

}