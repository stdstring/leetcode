#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxAdjacentDistance(std::vector<int> const &nums) const
    {
        int maxValue = 0;
        for (size_t index = 0; index < nums.size(); ++index)
            maxValue = std::max(maxValue, std::abs(nums[index] - nums[(index + 1) % nums.size()]));
        return maxValue;
    }
};

}

namespace MaxDiffBetweenElementsInCircularArrayTask
{

TEST(MaxDiffBetweenElementsInCircularArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxAdjacentDistance({1, 2, 4}));
    ASSERT_EQ(5, solution.maxAdjacentDistance({-5, -10, -5}));
}

}