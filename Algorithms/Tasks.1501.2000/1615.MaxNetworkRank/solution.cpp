#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximalNetworkRank(int n, std::vector<std::vector<int>> const &roads) const
    {
        std::vector<std::unordered_set<int>> neighbors(n);
        for (std::vector<int> const &road : roads)
        {
            neighbors[road[0]].emplace(road[1]);
            neighbors[road[1]].emplace(road[0]);
        }
        std::vector<int> cities(n, 0);
        std::iota(cities.begin(), cities.end(), 0);
        std::ranges::sort(cities, [&neighbors](int a, int b) { return neighbors[a].size() > neighbors[b].size(); });
        const int maxPossibleRank = static_cast<int>(neighbors[cities[0]].size() + neighbors[cities[1]].size());
        const int minPossibleRank = static_cast<int>(neighbors[cities[0]].size() + neighbors[cities[1]].size() - 1);
        if (neighbors[cities[0]].size() > neighbors[cities[1]].size())
        {
            for (size_t index = 1; (index < cities.size()) && (neighbors[cities[index]].size() == neighbors[cities[1]].size()); ++index)
            {
                if (!neighbors[cities[0]].contains(cities[index]))
                    return maxPossibleRank;
            }
            return minPossibleRank;
        }
        for (size_t index1 = 0; (index1 < cities.size()) && (neighbors[cities[index1]].size() == neighbors[cities[0]].size()); ++index1)
        {
            for (size_t index2 = index1 + 1; (index2 < cities.size()) && (neighbors[cities[index2]].size() == neighbors[cities[0]].size()); ++index2)
            {
                if (!neighbors[cities[index1]].contains(cities[index2]))
                    return maxPossibleRank;
            }
        }
        return minPossibleRank;
    }
};

}

namespace MaxNetworkRankTask
{

TEST(MaxNetworkRankTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maximalNetworkRank(4, {{0, 1}, {0, 3}, {1, 2}, {1, 3}}));
    ASSERT_EQ(5, solution.maximalNetworkRank(5, {{0, 1}, {0, 3}, {1, 2}, {1, 3}, {2, 3}, {2, 4}}));
    ASSERT_EQ(5, solution.maximalNetworkRank(8, {{0, 1}, {1, 2}, {2, 3}, {2, 4}, {5, 6}, {5, 7}}));
}

}