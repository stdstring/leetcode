#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool validPartition(std::vector<int> const &nums) const
    {
        std::vector<bool> dp(nums.size() + 1, false);
        dp[0] = true;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (!dp[index])
                continue;
            size_t numsRest = nums.size() - index;
            if ((numsRest >= 2) && (nums[index] == nums[index + 1]))
                dp[index + 2] = true;
            if ((numsRest >= 3) && (nums[index] == nums[index + 1]) && (nums[index + 1] == nums[index + 2]))
                dp[index + 3] = true;
            if ((numsRest >= 3) && ((nums[index + 1] - nums[index]) == 1) && ((nums[index + 2] - nums[index + 1]) == 1))
                dp[index + 3] = true;
        }
        return dp.back();
    }
};

}

namespace CheckIfValidPartitionForArrayTask
{

TEST(CheckIfValidPartitionForArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.validPartition({4, 4, 4, 5, 6}));
    ASSERT_EQ(false, solution.validPartition({1, 1, 1, 2}));
}

}