#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minScore(int n, std::vector<std::vector<int>> const &roads) const
    {
        std::vector<std::vector<Road>> cities(n, std::vector<Road>());
        for (std::vector<int> const &road : roads)
        {
            int a = road[0] - 1;
            int b = road[1] - 1;
            int distance = road[2];
            cities[a].emplace_back(b, distance);
            cities[b].emplace_back(a, distance);
        }
        int minDistance = cities[0].front().Distance;
        std::vector<bool> visited(n, false);
        visited[0] = true;
        std::queue<int> citiesQueue;
        citiesQueue.emplace(0);
        while (!citiesQueue.empty())
        {
            const int current = citiesQueue.front();
            citiesQueue.pop();
            for (Road const &road : cities[current])
            {
                minDistance = std::min(minDistance, road.Distance);
                if (!visited[road.Dest])
                {
                    citiesQueue.emplace(road.Dest);
                    visited[road.Dest] = true;
                }
            }
        }
        return minDistance;
    }

private:
    struct Road
    {
        Road(int dest, int distance) : Dest(dest), Distance(distance)
        {
        }

        int Dest;
        int Distance;
    };
};

}

namespace MinScoreOfPathBetweenTwoCitiesTask
{

TEST(MinScoreOfPathBetweenTwoCitiesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.minScore(4, {{1, 2, 9}, {2, 3, 6}, {2, 4, 5}, {1, 4, 7}}));
    ASSERT_EQ(2, solution.minScore(4, {{1, 2, 2}, {1, 3, 4}, {3, 4, 7}}));
}

}