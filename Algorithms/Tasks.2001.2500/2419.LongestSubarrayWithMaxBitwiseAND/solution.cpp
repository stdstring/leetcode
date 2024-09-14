#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestSubarray(std::vector<int> const &nums) const
    {
        int maxValue = std::ranges::max(nums);
        size_t bestSize = 1;
        size_t start = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (nums[index] == maxValue)
                bestSize = std::max(bestSize, index - start + 1);
            else
                start = index + 1;
        }
        return static_cast<int>(bestSize);
    }
};

}

namespace LongestSubarrayWithMaxBitwiseANDTask
{

TEST(LongestSubarrayWithMaxBitwiseANDTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.longestSubarray({1, 2, 3, 3, 2, 2}));
    ASSERT_EQ(1, solution.longestSubarray({1, 2, 3, 4}));
}

}