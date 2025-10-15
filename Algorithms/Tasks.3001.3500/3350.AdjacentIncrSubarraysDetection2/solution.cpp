#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxIncreasingSubarrays(std::vector<int> const &nums) const
    {
        int result = 1;
        int prevPortionSize = 0;
        int portionSize = 1;
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (nums[index - 1] >= nums[index])
            {
                prevPortionSize = portionSize;
                portionSize = 1;
                continue;
            }
            ++portionSize;
            result = std::max(result, std::min(prevPortionSize, portionSize));
            result = std::max(result, portionSize / 2);
        }
        return result;
    }
};

}

namespace AdjacentIncrSubarraysDetection2Task
{

TEST(AdjacentIncrSubarraysDetection2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxIncreasingSubarrays({2, 5, 7, 8, 9, 2, 3, 4, 3, 1}));
    ASSERT_EQ(2, solution.maxIncreasingSubarrays({1, 2, 3, 4, 4, 4, 4, 5, 6, 7}));
}

TEST(AdjacentIncrSubarraysDetection2TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.maxIncreasingSubarrays({19, 5}));
}

}