#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool divideArray(std::vector<int> const &nums) const
    {
        auto [minValue, maxValue] = std::ranges::minmax(nums);
        std::vector<bool> isEven(maxValue - minValue + 1, true);
        for (const int number : nums)
            isEven[number - minValue] = !isEven[number - minValue];
        return std::ranges::all_of(isEven, [](bool value){ return value; });
    }
};

}

namespace DivideArrayIntoEqualPairsTask
{

TEST(DivideArrayIntoEqualPairsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.divideArray({3, 2, 3, 2, 2, 2}));
    ASSERT_EQ(false, solution.divideArray({1, 2, 3, 4}));
}

TEST(DivideArrayIntoEqualPairsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.divideArray({1, 1}));
}

}