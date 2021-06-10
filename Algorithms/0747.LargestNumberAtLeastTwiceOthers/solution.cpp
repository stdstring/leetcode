#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int dominantIndex(std::vector<int> const &nums) const
    {
        constexpr int minNumber = 0;
        size_t candidateIndex = nums.size();
        int maxValue = minNumber;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            int number = nums[index];
            if (candidateIndex == nums.size())
            {
                if (number >= 2 * maxValue)
                    candidateIndex = index;
                else
                    maxValue = std::max(maxValue, number);
            }
            else
            {
                if (number > nums[candidateIndex])
                {
                    maxValue = std::max(maxValue, nums[candidateIndex]);
                    candidateIndex = index;
                }
                else
                    maxValue = std::max(maxValue, number);
                if (nums[candidateIndex] < 2 * maxValue)
                {
                    maxValue = std::max(maxValue, nums[candidateIndex]);
                    candidateIndex = nums.size();
                }
            }
        }
        return candidateIndex == nums.size() ? -1 : static_cast<int>(candidateIndex);
    }
};

}

namespace LargestNumberAtLeastTwiceOthersTask
{

TEST(LargestNumberAtLeastTwiceOthersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.dominantIndex({3, 6, 1, 0}));
    ASSERT_EQ(-1, solution.dominantIndex({1, 2, 3, 4}));
    ASSERT_EQ(0, solution.dominantIndex({1}));
}

}