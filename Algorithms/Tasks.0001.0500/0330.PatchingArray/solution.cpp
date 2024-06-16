#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minPatches(std::vector<int> const &nums, int n) const
    {
        // similar to https://leetcode.com/problems/maximum-number-of-consecutive-values-you-can-make/description/
        const long long maxNumber = n;
        long long number = 1;
        int patchCount = 0;
        size_t index = 0;
        while (number <= maxNumber)
        {
            if ((index < nums.size()) && (nums[index] <= number))
            {
                number += nums[index];
                ++index;
            }
            else
            {
                number += number;
                ++patchCount;
            }
        }
        return patchCount;
    }
};

}

namespace PatchingArrayTask
{

TEST(PatchingArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minPatches({1, 3}, 6));
    ASSERT_EQ(2, solution.minPatches({1, 5, 10}, 20));
    ASSERT_EQ(0, solution.minPatches({1, 2, 2}, 5));
}

}