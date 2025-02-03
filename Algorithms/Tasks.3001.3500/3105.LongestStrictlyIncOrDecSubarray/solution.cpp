#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestMonotonicSubarray(std::vector<int> const &nums) const
    {
        size_t longestSubarray = 1;
        size_t increasingStart = 0;
        size_t decreasingStart = 0;
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (nums[index - 1] < nums[index])
                longestSubarray = std::max(longestSubarray, index - increasingStart + 1);
            else
                increasingStart = index;
            if (nums[index - 1] > nums[index])
                longestSubarray = std::max(longestSubarray, index - decreasingStart + 1);
            else
                decreasingStart = index;
        }
        return static_cast<int>(longestSubarray);
    }
};

}

namespace LongestStrictlyIncOrDecSubarrayTask
{

TEST(LongestStrictlyIncOrDecSubarrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.longestMonotonicSubarray({1, 4, 3, 3, 2}));
    ASSERT_EQ(1, solution.longestMonotonicSubarray({3, 3, 3, 3}));
    ASSERT_EQ(3, solution.longestMonotonicSubarray({3, 2, 1}));
}

}