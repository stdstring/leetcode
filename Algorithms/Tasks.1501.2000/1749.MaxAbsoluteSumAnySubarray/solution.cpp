#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxAbsoluteSum(std::vector<int> const &nums) const
    {
        int result = std::abs(nums[0]);
        int maxSum = nums[0];
        int minSum = nums[0];
        for (size_t index = 1; index < nums.size(); ++index)
        {
            maxSum = std::max(maxSum + nums[index], nums[index]);
            minSum = std::min(minSum + nums[index], nums[index]);
            result = std::max(result, std::max(std::abs(maxSum), std::abs(minSum)));
        }
        return result;
    }
};

}

namespace MaxAbsoluteSumAnySubarrayTask
{

TEST(MaxAbsoluteSumAnySubarrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.maxAbsoluteSum({1, -3, 2, 3, -4}));
    ASSERT_EQ(8, solution.maxAbsoluteSum({2, -5, 1, -4, 3, -2}));
}

}