#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findLengthOfLCIS(std::vector<int> const &nums) const
    {
        size_t bestLength = 1;
        size_t currentLength = 1;
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (nums[index] > nums[index - 1])
                ++currentLength;
            else
                currentLength = 1;
            bestLength = std::max(bestLength, currentLength);
        }
        return static_cast<int>(bestLength);
    }
};

}

namespace LongestContinuousIncSubseqTask
{

TEST(LongestContinuousIncSubseqTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.findLengthOfLCIS({1, 3, 5, 4, 7}));
    ASSERT_EQ(1, solution.findLengthOfLCIS({2, 2, 2, 2, 2}));
}

TEST(LongestContinuousIncSubseqTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.findLengthOfLCIS({2, 1, 3}));
    ASSERT_EQ(1, solution.findLengthOfLCIS({1}));
}

}