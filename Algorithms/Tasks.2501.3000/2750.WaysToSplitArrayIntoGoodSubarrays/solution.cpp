#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfGoodSubarraySplits(std::vector<int> const &nums) const
    {
        constexpr size_t modValue = 1000000007;
        size_t splitsCount = 0;
        size_t prevOneIndex = nums.size();
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (nums[index] == 0)
                continue;
            if (prevOneIndex == nums.size())
                splitsCount = 1;
            else
                splitsCount = (splitsCount * (index - prevOneIndex)) % modValue;
            prevOneIndex = index;
        }
        return static_cast<int>(splitsCount);
    }
};

}

namespace WaysToSplitArrayIntoGoodSubarraysTask
{

TEST(WaysToSplitArrayIntoGoodSubarraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numberOfGoodSubarraySplits({0, 1, 0, 0, 1}));
    ASSERT_EQ(1, solution.numberOfGoodSubarraySplits({0, 1, 0}));
}

TEST(WaysToSplitArrayIntoGoodSubarraysTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(12, solution.numberOfGoodSubarraySplits({0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0}));
    ASSERT_EQ(60, solution.numberOfGoodSubarraySplits({0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0}));
    ASSERT_EQ(0, solution.numberOfGoodSubarraySplits({0}));
}

}