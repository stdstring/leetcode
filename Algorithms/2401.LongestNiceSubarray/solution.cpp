#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestNiceSubarray(std::vector<int> const &nums) const
    {
        int totalAndValue = 0;
        size_t niceSubarraySize = 0;
        for (size_t start = 0, end = 0; end < nums.size();)
        {
            if ((nums[end] & totalAndValue) == 0)
            {
                totalAndValue |= nums[end];
                ++end;
                niceSubarraySize = std::max(niceSubarraySize, end - start);
            }
            else
            {
                totalAndValue &= (~nums[start]);
                ++start;
                niceSubarraySize = std::max(niceSubarraySize, end - start);
            }
        }
        return static_cast<int>(niceSubarraySize);
    }
};

}

namespace LongestNiceSubarrayTask
{

TEST(LongestNiceSubarrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.longestNiceSubarray({1, 3, 8, 48, 10}));
    ASSERT_EQ(1, solution.longestNiceSubarray({3, 1, 5, 11, 13}));
}

}