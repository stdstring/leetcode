#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findMaxK(std::vector<int> const &nums) const
    {
        constexpr int maxValue = 1000;
        constexpr size_t numbersCount = maxValue + 1;
        std::vector<bool> negativeNumbers(numbersCount, false);
        std::vector<bool> positiveNumbers(numbersCount, false);
        for (const int num : nums)
        {
            if (num >= 0)
                positiveNumbers[num] = true;
            if (num <= 0)
                negativeNumbers[std::abs(num)] = true;

        }
        for (size_t index = 0; index < numbersCount; ++index)
        {
            if (positiveNumbers[numbersCount - 1 - index] && negativeNumbers[numbersCount - 1 - index])
                return static_cast<int>(numbersCount - 1 - index);
        }
        return -1;
    }
};

}

namespace LargestPosIntThatExistsWithItsNegTask
{

TEST(LargestPosIntThatExistsWithItsNegTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.findMaxK({-1, 2, -3, 3}));
    ASSERT_EQ(7, solution.findMaxK({-1, 10, 6, 7, -7, 1}));
    ASSERT_EQ(-1, solution.findMaxK({-10, 8, 6, 7, -2, -3}));
}

}
