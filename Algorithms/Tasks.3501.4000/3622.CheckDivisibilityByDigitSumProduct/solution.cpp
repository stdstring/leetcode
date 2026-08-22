#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkDivisibility(int n) const
    {
        const int number = n;
        int digitSum = 0;
        int digitProduct = 1;
        for (; n > 0; n /= 10)
        {
            const int digit = n % 10;
            digitSum += digit;
            digitProduct *= digit;
        }
        return (number % (digitSum + digitProduct)) == 0;
    }
};

}

namespace CheckDivisibilityByDigitSumProductTask
{

TEST(CheckDivisibilityByDigitSumProductTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkDivisibility(99));
    ASSERT_EQ(false, solution.checkDivisibility(23));
}

}