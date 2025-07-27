#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countHillValley(std::vector<int> const &nums) const
    {
        size_t result = 0;
        for (size_t index = 1, start = 1; index < nums.size(); ++index)
        {
            if (nums[index] == nums[start])
                continue;
            if (((nums[start - 1] < nums[start]) && (nums[index] < nums[start])) ||
                ((nums[start - 1] > nums[start]) && (nums[index] > nums[start])))
                ++result;
            start = index;
        }
        return static_cast<int>(result);
    }
};

}

namespace CountHillsAndValleysInArrayTask
{

TEST(CountHillsAndValleysInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.countHillValley({2, 4, 1, 1, 6, 5}));
    ASSERT_EQ(0, solution.countHillValley({6, 6, 5, 5, 4, 1}));
}

TEST(CountHillsAndValleysInArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.countHillValley({6, 5, 10}));
}

}