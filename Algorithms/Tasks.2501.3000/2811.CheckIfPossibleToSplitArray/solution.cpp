#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canSplitArray(std::vector<int> const &nums, int m) const
    {
        if (nums.size() <= 2)
            return true;
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if ((nums[index - 1] + nums[index]) >= m)
                return true;
        }
        return false;
    }
};

}

namespace CheckIfPossibleToSplitArrayTask
{

TEST(CheckIfPossibleToSplitArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canSplitArray({2, 2, 1}, 4));
    ASSERT_EQ(false, solution.canSplitArray({2, 1, 3}, 5));
    ASSERT_EQ(true, solution.canSplitArray({2, 3, 3, 2, 3}, 6));
}

TEST(CheckIfPossibleToSplitArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canSplitArray({1}, 2));
    ASSERT_EQ(true, solution.canSplitArray({4, 1, 3, 2, 4}, 6));
}

}