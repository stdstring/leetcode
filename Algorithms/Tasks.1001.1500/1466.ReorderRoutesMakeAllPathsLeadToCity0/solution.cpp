#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minReorder(int n, std::vector<std::vector<int>> const &connections) const
    {
        std::vector<std::vector<TRoad>> cities(n, std::vector<TRoad>());
        for (std::vector<int> const &road : connections)
        {
            size_t fromCity = road[0];
            size_t toCity = road[1];
            cities[fromCity].emplace_back(toCity, true);
            cities[toCity].emplace_back(fromCity, false);
        }
        return static_cast<int>(calcInverseRoads(cities, 0, cities.size()));
    }

private:
    typedef std::pair<size_t, bool> TRoad;

    [[nodiscard]] size_t calcInverseRoads(std::vector<std::vector<TRoad>> const &cities, size_t current, size_t parent) const
    {
        size_t inverseRoadsCount = 0;
        for (TRoad const &road : cities[current])
        {
            if (road.first == parent)
                continue;
            if (road.second)
                ++inverseRoadsCount;
            inverseRoadsCount += calcInverseRoads(cities, road.first, current);
        }
        return inverseRoadsCount;
    }
};

}

namespace ReorderRoutesMakeAllPathsLeadToCity0Task
{

TEST(ReorderRoutesMakeAllPathsLeadToCity0TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minReorder(6, {{0, 1}, {1, 3}, {2, 3}, {4, 0}, {4, 5}}));
    ASSERT_EQ(2, solution.minReorder(5, {{1, 0}, {1, 2}, {3, 2}, {3, 4}}));
    ASSERT_EQ(0, solution.minReorder(3, {{1, 0}, {2, 0}}));
}

}