#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numBusesToDestination(std::vector<std::vector<int>> const &routes, int source, int target) const
    {
        if (source == target)
            return 0;
        std::unordered_map<int, std::vector<size_t>> stopRoutesMap;
        for (size_t index = 0; index < routes.size(); ++index)
        {
            for (int stop : routes[index])
                stopRoutesMap[stop].push_back(index);
        }
        // bfs
        std::unordered_set<int> visitedStops;
        visitedStops.emplace(source);
        std::vector<bool> visitedRoutes(routes.size(), false);
        int busCount = 0;
        std::queue<int> queue;
        queue.emplace(source);
        while (!queue.empty())
        {
            const size_t portionSize = queue.size();
            for (size_t index = 0; index < portionSize; ++index)
            {
                int current = queue.front();
                if (current == target)
                    return busCount;
                queue.pop();
                for (const size_t route : stopRoutesMap[current])
                {
                    if (visitedRoutes[route])
                        continue;
                    visitedRoutes[route] = true;
                    for (int next : routes[route])
                    {
                        if (visitedStops.contains(next))
                            continue;
                        visitedStops.emplace(next);
                        queue.emplace(next);
                    }
                }
            }
            ++busCount;
        }
        return -1;
    }
};

}

namespace BusRoutesTask
{

TEST(BusRoutesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.numBusesToDestination({{1, 2, 7}, {3, 6, 7}}, 1, 6));
    ASSERT_EQ(-1, solution.numBusesToDestination({{7, 12}, {4, 5, 15}, {6}, {15, 19}, {9, 12, 13}}, 15, 12));
}

TEST(BusRoutesTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.numBusesToDestination({{1, 7}, {3, 5}}, 5, 5));
}

}
