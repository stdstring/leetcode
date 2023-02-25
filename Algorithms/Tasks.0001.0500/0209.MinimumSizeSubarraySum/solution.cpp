#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int minSubArrayLen(int s, std::vector<int> const &nums) const
    {
        if (nums.empty())
            return 0;
        size_t left = 0;
        size_t right = 0;
        size_t minLength = 0;
        int sum = 0;
        while (right < nums.size())
        {
            if (sum < s)
            {
                sum += nums[right];
                ++right;
            }
            else
            {
                sum -= nums[left];
                ++left;
            }
            if (sum >= s)
            {
                minLength = minLength == 0 ? right - left : std::min(right - left, minLength);
            }
        }
        while ((sum - nums[left]) >= s)
        {
            sum -= nums[left];
            ++left;
        }
        if (sum >= s)
            minLength = minLength == 0 ? right - left : std::min(right - left, minLength);
        return static_cast<int>(minLength);
    }
};

}

namespace MinimumSizeSubarraySumTask
{

TEST(MinimumSizeSubarraySumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.minSubArrayLen(7, {2, 3, 1, 2, 4, 3}));
}

TEST(MinimumSizeSubarraySumTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.minSubArrayLen(100, {}));
    ASSERT_EQ(0, solution.minSubArrayLen(3, {1, 1}));
    ASSERT_EQ(8, solution.minSubArrayLen(213, {12, 28, 83, 4, 25, 26, 25, 2, 25, 25, 25, 12}));
}

}