#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findUnsortedSubarray(std::vector<int> const &nums) const
    {
        size_t unsortedSubarrayStart = nums.size();
        size_t unsortedSubarraySize = 0;
        int unsortedSubarrayMin = INT_MAX;
        int maxValue = nums[0];
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (nums[index] < maxValue)
            {
                unsortedSubarrayStart = unsortedSubarrayStart == nums.size() ? calcUnsortedSubarrayStart(nums, index) : updateUnsortedSubarrayStart(nums, nums[index], unsortedSubarrayStart, unsortedSubarrayMin);
                unsortedSubarrayMin = std::min(unsortedSubarrayMin, nums[index]);
                unsortedSubarraySize = index - unsortedSubarrayStart + 1;
            }
            else
                maxValue = nums[index];
        }
        return static_cast<int>(unsortedSubarraySize);
    }

private:
    size_t calcUnsortedSubarrayStart(std::vector<int> const &nums, size_t currentIndex) const
    {
        const int currentValue = nums[currentIndex--];
        while (nums[currentIndex] > currentValue)
        {
            if (currentIndex == 0)
                return 0;
            --currentIndex;
        }
        return currentIndex + 1;
    }

    size_t updateUnsortedSubarrayStart(std::vector<int> const &nums, int currentValue, size_t unsortedSubarrayStart, int unsortedSubarrayMin) const
    {
        if (currentValue >= unsortedSubarrayMin)
            return unsortedSubarrayStart;
        while (nums[unsortedSubarrayStart] > currentValue)
        {
            if (unsortedSubarrayStart == 0)
                return 0;
            --unsortedSubarrayStart;
        }
        return unsortedSubarrayStart + 1;
    }
};

}

namespace ShortestUnsortedContinuousSubarrayTask
{

TEST(ShortestUnsortedContinuousSubarrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.findUnsortedSubarray({2, 6, 4, 8, 10, 9, 15}));
    ASSERT_EQ(0, solution.findUnsortedSubarray({1, 2, 3, 4}));
    ASSERT_EQ(0, solution.findUnsortedSubarray({1}));
}

TEST(ShortestUnsortedContinuousSubarrayTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(3, solution.findUnsortedSubarray({1, 2, 5, 4, 3}));
    ASSERT_EQ(4, solution.findUnsortedSubarray({1, 3, 2, 2, 2}));
}

}