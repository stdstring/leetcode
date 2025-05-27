#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int differenceOfSums(int n, int m) const
    {
        int num1 = 0;
        int num2 = 0;
        for (int number = 1; number <= n; ++number)
        {
            ((number % m == 0) ? num2 : num1) += number;
        }
        return num1 - num2;
    }
};

}

namespace DivisibleAndNonDivisibleSumsDiffTask
{

TEST(DivisibleAndNonDivisibleSumsDiffTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(19, solution.differenceOfSums(10, 3));
    ASSERT_EQ(15, solution.differenceOfSums(5, 6));
    ASSERT_EQ(-15, solution.differenceOfSums(5, 1));
}

}