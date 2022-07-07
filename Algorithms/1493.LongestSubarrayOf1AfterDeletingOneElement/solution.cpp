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
        size_t lastZeroIndex = 0;
        // init lastZeroIndex
        while ((lastZeroIndex < nums.size()) && (nums[lastZeroIndex] == 1))
            ++lastZeroIndex;
        if (lastZeroIndex == nums.size())
            return static_cast<int>(nums.size() - 1);
        size_t maxSubarraySize = lastZeroIndex;
        size_t subarrayStart = 0;
        for (size_t index = lastZeroIndex + 1; index < nums.size(); ++index)
        {
            if (nums[index] == 0)
            {
                subarrayStart = lastZeroIndex + 1;
                lastZeroIndex = index;
            }
            if (subarrayStart < index)
               maxSubarraySize = std::max(maxSubarraySize, index - subarrayStart);
        }
        return static_cast<int>(maxSubarraySize);
    }
};

}

namespace LongestSubarrayOf1AfterDeletingOneElementTask
{

TEST(LongestSubarrayOf1AfterDeletingOneElementTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.longestSubarray({1, 1, 0, 1}));
    ASSERT_EQ(5, solution.longestSubarray({0, 1, 1, 1, 0, 1, 1, 0, 1}));
    ASSERT_EQ(2, solution.longestSubarray({1, 1, 1}));
}

TEST(LongestSubarrayOf1AfterDeletingOneElementTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.longestSubarray({1, 0, 0, 0, 0}));
}

}