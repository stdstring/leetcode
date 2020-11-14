#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maxSubArray(std::vector<int> const &nums) const
    {
        int best = nums[0];
        int sum = nums[0];
        for (size_t index = 1; index < nums.size(); ++index)
        {
            sum = std::max(nums[index], sum + nums[index]);
            best = std::max(best, sum);
        }
        return best;
    }
};

}

namespace MaximumSubarrayTask
{

TEST(MaximumSubarrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.maxSubArray({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
    ASSERT_EQ(1, solution.maxSubArray({1}));
    ASSERT_EQ(0, solution.maxSubArray({0}));
    ASSERT_EQ(-1, solution.maxSubArray({-1}));
    ASSERT_EQ(-2147483647, solution.maxSubArray({-2147483647}));
}

}