#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumCost(std::vector<int> const &nums) const
    {
        int min1 = std::min(nums[1], nums[2]);
        int min2 = std::max(nums[1], nums[2]);
        for (size_t index = 3; index < nums.size(); ++index)
        {
            const int current = nums[index];
            if (current <= min1)
            {
                min2 = min1;
                min1 = current;
            }
            else if (current < min2)
                min2 = current;
        }
        return nums[0] + min1 + min2;
    }
};

}

namespace DivideArrayIntoSubarraysWithMinCost1Task
{

TEST(DivideArrayIntoSubarraysWithMinCost1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.minimumCost({1, 2, 3, 12}));
    ASSERT_EQ(12, solution.minimumCost({5, 4, 3}));
    ASSERT_EQ(12, solution.minimumCost({10, 3, 1, 1}));
}

TEST(DivideArrayIntoSubarraysWithMinCost1TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(11, solution.minimumCost({1, 6, 49, 35, 41, 4, 31, 39, 36, 39}));
}

}