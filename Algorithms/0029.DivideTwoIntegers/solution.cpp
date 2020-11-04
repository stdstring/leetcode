#include <limits>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int divide(int dividend, int divisor) const
    {
        long long ldividend = dividend;
        if (dividend < 0)
            ldividend = -ldividend;
        long long ldivisor = divisor;
        if (divisor < 0)
            ldivisor = -ldivisor;
        const bool negativeResult = (dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0);
        if (ldividend == ldivisor)
            return negativeResult ? -1 : 1;
        if (ldividend < ldivisor)
            return 0;
        if (ldivisor == 1)
        {
            ldividend = negativeResult ? -ldividend : ldividend;
            return ldividend > std::numeric_limits<int>::max() ? std::numeric_limits<int>::max() : static_cast<int>(ldividend);
        }
        long long quotient = 0;
        long long remainder = 0;
        // from https://en.wikipedia.org/wiki/Division_algorithm
        for (int i = calcHighestSignificantBitNumber(ldividend); i >= 0; --i)
        {
            remainder <<= 1;
            if ((ldividend & (1ll << i)) > 0)
                remainder |= 1;
            if (remainder >= ldivisor)
            {
                remainder -= ldivisor;
                quotient |= (1ll << i);
            }
        }
        return static_cast<int>(negativeResult ? -quotient : quotient);
    }

private:
    int calcHighestSignificantBitNumber(long long n) const
    {
        for (long long number = 31; number >= 0; --number)
        {
            if ((1ll << number) <= n)
                return static_cast<int>(number);
        }
        return 0;
    }
};

}

namespace DivideTwoIntegersTask
{

TEST(DivideTwoIntegersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.divide(10, 3));
    ASSERT_EQ(-2, solution.divide(7, -3));
}

TEST(DivideTwoIntegersTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(-1, solution.divide(-1, 1));
    ASSERT_EQ(std::numeric_limits<int>::max(), solution.divide(INT_MIN, -1));
    ASSERT_EQ(2147483647, solution.divide(2147483647, 1));
    ASSERT_EQ(715827882, solution.divide(INT_MIN, -3));
    ASSERT_EQ(-1073741824, solution.divide(INT_MIN, 2));
}

}