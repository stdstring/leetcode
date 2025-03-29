#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countPaths(int n, std::vector<std::vector<int>> const &roads) const
    {
        typedef std::pair<int, size_t> TLink;
        constexpr int modValue = 1000000007;
        // graph
        std::vector<std::vector<TLink>> graph(n);
        for (std::vector<int> const &road : roads)
        {
            graph[road[0]].emplace_back(road[1], road[2]);
            graph[road[1]].emplace_back(road[0], road[2]);
        }
        // paths
        std::vector<size_t> shortestTime(n, LLONG_MAX);
        shortestTime[0] = 0;
        std::vector<int> pathCounts(n, 0);
        pathCounts[0] = 1;
        typedef std::pair<int, size_t> TPath;
        auto cmp = [](TPath const &l, TPath const &r)
        {
            return (l.second > r.second) || ((l.second == r.second) && (l.first > r.first));
        };
        std::priority_queue<TPath, std::vector<TPath>, decltype(cmp)> queue(cmp);
        queue.emplace(0, 0);
        while (!queue.empty())
        {
            auto [node, path] = queue.top();
            queue.pop();
            for (auto &[neighbor, road] : graph[node])
            {
                const size_t neighborPath = path + road;
                if (neighborPath < shortestTime[neighbor])
                {
                    pathCounts[neighbor] = pathCounts[node];
                    shortestTime[neighbor] = neighborPath;
                    queue.emplace(neighbor, neighborPath);
                }
                else if (neighborPath == shortestTime[neighbor])
                    pathCounts[neighbor] = (pathCounts[neighbor] + pathCounts[node]) % modValue;
            }
        }
        return pathCounts.back();
    }
};

}

namespace NumberWaysArriveAtDestinationTask
{

TEST(NumberWaysArriveAtDestinationTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.countPaths(7, {{0, 6, 7}, {0, 1, 2}, {1, 2, 3}, {1, 3, 3}, {6, 3, 3}, {3, 5, 1}, {6, 5, 1}, {2, 5, 1}, {0, 4, 5}, {4, 6, 2}}));
    ASSERT_EQ(1, solution.countPaths(2, {{1, 0, 10}}));
}

}