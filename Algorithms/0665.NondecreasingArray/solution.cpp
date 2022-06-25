#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkPossibility(std::vector<int> const &nums) const
    {
        if (nums.size() == 1)
            return true;
        size_t bigIndex = nums.size();
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (nums[index - 1] > nums[index])
            {
                if (bigIndex != nums.size())
                    return false;
                bigIndex = index - 1;
            }
        }
        return (bigIndex == nums.size()) ||
               (bigIndex == 0) ||
               (bigIndex == nums.size() - 2) ||
               (nums[bigIndex - 1] <= nums[bigIndex + 1]) ||
               (nums[bigIndex] <= nums[bigIndex + 2]);
    }
};

}

namespace NondecreasingArrayTask
{

TEST(NondecreasingArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkPossibility({4, 2, 3}));
    ASSERT_EQ(false, solution.checkPossibility({4, 2, 1}));
}

TEST(NondecreasingArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkPossibility({5, 7, 1, 8}));
    ASSERT_EQ(true, solution.checkPossibility({-1, 4, 2, 3}));
    ASSERT_EQ(false, solution.checkPossibility({3, 4, 2, 3}));
}

}