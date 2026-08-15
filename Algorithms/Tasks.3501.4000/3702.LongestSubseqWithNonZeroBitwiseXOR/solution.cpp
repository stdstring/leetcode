#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestSubsequence(std::vector<int> const &nums) const
    {
        bool hasNonZero = false;
        int total = 0;
        for (int number : nums)
        {
            total ^= number;
            hasNonZero |= (number > 0);
        }
        if (!hasNonZero)
            return 0;
        return static_cast<int>(nums.size()) - (total == 0 ? 1 : 0);
    }
};

}

namespace LongestSubseqWithNonZeroBitwiseXORTask
{

TEST(LongestSubseqWithNonZeroBitwiseXORTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.longestSubsequence({1, 2, 3}));
    ASSERT_EQ(3, solution.longestSubsequence({2, 3, 4}));
}

TEST(LongestSubseqWithNonZeroBitwiseXORTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.longestSubsequence({0, 0, 0, 0}));
}

}