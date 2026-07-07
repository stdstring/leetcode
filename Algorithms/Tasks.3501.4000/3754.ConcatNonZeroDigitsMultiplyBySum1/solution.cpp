#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long sumAndMultiply(int n) const
    {
        long long newNumber = 0;
        long long factor = 1;
        long long digitSum = 0;
        for (; n > 0; n /= 10)
        {
            const int digit = n % 10;
            digitSum += digit;
            if (digit > 0)
            {
                newNumber = newNumber + factor * digit;
                factor *= 10;
            }
        }
        return digitSum * newNumber;
    }
};

}

namespace ConcatNonZeroDigitsMultiplyBySum1Task
{

TEST(ConcatNonZeroDigitsMultiplyBySum1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(12340, solution.sumAndMultiply(10203004));
    ASSERT_EQ(1, solution.sumAndMultiply(1000));
}

}