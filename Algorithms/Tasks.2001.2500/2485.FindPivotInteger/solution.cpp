#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int pivotInteger(int n) const
    {
        int rightSum = (1 + n) * n / 2;
        int leftSum = 0;
        for (int x = 1; leftSum <= rightSum; ++x)
        {
            leftSum += x;
            if (leftSum == rightSum)
                return x;
            rightSum -= x;
        }
        return -1;
    }
};

}

namespace FindPivotIntegerTask
{

TEST(FindPivotIntegerTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.pivotInteger(8));
    ASSERT_EQ(1, solution.pivotInteger(1));
    ASSERT_EQ(-1, solution.pivotInteger(4));
}

}