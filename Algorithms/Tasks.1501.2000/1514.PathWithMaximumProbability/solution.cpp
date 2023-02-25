#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    double maxProbability(int n, std::vector<std::vector<int>> const &edges, std::vector<double> const &succProb, int start, int end) const
    {
        std::vector<std::vector<std::pair<int, double>>> graph(n, std::vector<std::pair<int, double>>());
        for (size_t index = 0; index < edges.size(); ++index)
        {
            graph[edges[index][0]].emplace_back(edges[index][1], succProb[index]);
            graph[edges[index][1]].emplace_back(edges[index][0], succProb[index]);
        }
        std::vector<bool> processed(n, false);
        auto compare = [](std::pair<int, double> const &left, std::pair<int, double> const &right) { return left.second < right.second; };
        std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, decltype(compare)> queue(compare);
        queue.push({start, 1.0});
        while (!queue.empty())
        {
            const int current = queue.top().first;
            const double currentProb = queue.top().second;
            queue.pop();
            if (processed[current])
                continue;
            if (current == end)
                return currentProb;
            processed[current] = true;
            for (std::pair<int, double> const &edge : graph[current])
            {
                if (processed[edge.first])
                    continue;
                double prob = currentProb * edge.second;
                queue.push({edge.first, prob});
            }
        }
        return 0;
    }
};

}

namespace PathWithMaximumProbabilityTask
{

TEST(PathWithMaximumProbabilityTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(0.25000, solution.maxProbability(3, {{0, 1}, {1, 2}, {0, 2}}, {0.5, 0.5, 0.2}, 0, 2));
    ASSERT_EQ(0.30000, solution.maxProbability(3, {{0, 1}, {1, 2}, {0, 2}}, {0.5, 0.5, 0.3}, 0, 2));
    ASSERT_EQ(0.00000, solution.maxProbability(3, {{0, 1}}, {0.5}, 0, 2));
}

}