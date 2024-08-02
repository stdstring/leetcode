#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minSwaps(std::vector<int> const &nums) const
    {
        const size_t onesCount = std::ranges::count(nums, 1);
        if (nums.size() == onesCount)
            return 0;
        size_t slidingWindowValue = 0;
        for (size_t index = 0; index < onesCount; ++index)
            slidingWindowValue += nums[index];
        size_t swapCount = onesCount - slidingWindowValue;
        for (size_t index = onesCount; index < 2 * nums.size(); ++index)
        {
            slidingWindowValue -= nums[(index - onesCount) % nums.size()];
            slidingWindowValue += nums[index % nums.size()];
            swapCount = std::min(swapCount, onesCount - slidingWindowValue);
        }
        return static_cast<int>(swapCount);
    }
};

}

namespace MinSwapsToGroupAll1Together2Task
{

TEST(MinSwapsToGroupAll1Together2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minSwaps({0, 1, 0, 1, 1, 0, 0}));
    ASSERT_EQ(2, solution.minSwaps({0, 1, 1, 1, 0, 0, 1, 1, 0}));
    ASSERT_EQ(0, solution.minSwaps({1, 1, 0, 0, 1}));
}

TEST(MinSwapsToGroupAll1Together2TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minSwaps({1, 1, 1, 0, 0, 1, 0, 1, 1, 0}));
}

}