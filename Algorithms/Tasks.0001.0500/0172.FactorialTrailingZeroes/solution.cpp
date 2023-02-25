#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int trailingZeroes(int n) const
    {
        int zeroesCount = 0;
        int fivePower = 5;
        while (fivePower <= n)
        {
            zeroesCount += (n / fivePower);
            fivePower *= 5;
        }
        return zeroesCount;
    }
};

}

namespace FactorialTrailingZeroesTask
{

TEST(FactorialTrailingZeroesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(0, solution.trailingZeroes(3));
    ASSERT_EQ(1, solution.trailingZeroes(5));
    ASSERT_EQ(0, solution.trailingZeroes(0));
}

}