#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    double myPow(double x, int n) const
    {
        if (n == 0)
            return 1;
        if (n == 1)
            return x;
        if (n == 2)
            return x * x;
        if (n == -1)
            return 1 / x;
        if (n == -2)
            return 1 / (x * x);
        if (n > 0)
        {
            const double halfPowerValue = myPow(x, n / 2);
            const double result = halfPowerValue * halfPowerValue;
            return n % 2 == 0 ? result : x * result;
        }
        else
        {
            const double halfPowerValue = myPow(x, n / 2);
            const double result = halfPowerValue * halfPowerValue;
            return n % 2 == 0 ? result : result / x;
        }
    }
};

}

namespace PowTask
{

TEST(PowTaskTests, Examples)
{
    const Solution solution;
    ASSERT_DOUBLE_EQ(1024.00000, solution.myPow(2.00000, 10));
    ASSERT_DOUBLE_EQ(9.26100, solution.myPow(2.10000, 3));
    ASSERT_DOUBLE_EQ(0.25000, solution.myPow(2.00000, -2));
}

TEST(PowTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_DOUBLE_EQ(1.00000, solution.myPow(1.00000, 2147483647));
    ASSERT_DOUBLE_EQ(4.00000, solution.myPow(-2.00000, 2));
}

}