#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> relocateMarbles(std::vector<int> const &nums, std::vector<int> const &moveFrom, std::vector<int> const &moveTo) const
    {
        std::set<int> positions(nums.cbegin(), nums.cend());
        for (size_t index = 0; index < moveFrom.size(); ++index)
        {
            positions.erase(moveFrom[index]);
            positions.emplace(moveTo[index]);
        }
        return std::vector<int>(positions.cbegin(), positions.cend());
    }
};

}

namespace RelocateMarblesTask
{

TEST(RelocateMarblesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({5, 6, 8, 9}), solution.relocateMarbles({1, 6, 7, 8}, {1, 7, 2}, {2, 9, 5}));
    ASSERT_EQ(std::vector<int>({2}), solution.relocateMarbles({1, 1, 3, 3}, {1, 3}, {2, 2}));
}

}