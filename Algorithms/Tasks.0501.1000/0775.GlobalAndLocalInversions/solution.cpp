#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isIdealPermutation(std::vector<int> const &nums) const
    {
        for (size_t index = 0; index < nums.size(); ++index)
        {
            const int number = nums[index];
            const int position = static_cast<int>(index);
            if (std::abs(number - position) > 1)
                return false;
        }
        return true;
    }
};

}

namespace GlobalAndLocalInversionsTask
{

TEST(GlobalAndLocalInversionsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isIdealPermutation({1, 0, 2}));
    ASSERT_EQ(false, solution.isIdealPermutation({1, 2, 0}));
}

TEST(GlobalAndLocalInversionsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.isIdealPermutation({2, 1, 0}));
}

}