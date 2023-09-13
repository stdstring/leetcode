#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> restoreArray(std::vector<std::vector<int>> const &adjacentPairs) const
    {
        std::unordered_map<int, std::vector<int>> neighborMap;
        for (std::vector<int> const &pair : adjacentPairs)
        {
            neighborMap[pair[0]].emplace_back(pair[1]);
            neighborMap[pair[1]].emplace_back(pair[0]);
        }
        int start = INT_MAX;
        for (auto const &[number, neighbors] : neighborMap)
        {
            if (neighbors.size() == 1)
                start = std::min(start, number);
        }
        std::vector<int> result(adjacentPairs.size() + 1, 0);
        result[0] = start;
        for (size_t index = 0; index < result.size() - 1; ++index)
        {
            std::vector<int> const &neighbors(neighborMap[result[index]]);
            if (index == 0)
                result[index + 1] = neighbors[0];
            else
                result[index + 1] = neighbors[0] == result[index - 1] ? neighbors[1] : neighbors[0];
        }
        return result;
    }
};

}

namespace RestoreArrayFromAdjacentPairsTask
{

TEST(RestoreArrayFromAdjacentPairsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 3, 4}), solution.restoreArray({{2, 1}, {3, 4}, {3, 2}}));
    ASSERT_EQ(std::vector<int>({-3, 1, 4, -2}), solution.restoreArray({{4, -2}, {1, 4}, {-3, 1}}));
    ASSERT_EQ(std::vector<int>({-100000, 100000}), solution.restoreArray({{100000, -100000}}));
}

}