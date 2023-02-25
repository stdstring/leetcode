#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int mySqrt(int x) const
    {
        if (x == 1)
            return 1;
        long long left = 0;
        long long right = x;
        while (right - left > 1)
        {
            const long long middle = (right + left) / 2;
            const long long product = middle * middle;
            if (product == x)
                return static_cast<int>(middle);
            if (product < x)
                left = middle;
            else if (product > x)
                right = middle;
        }
        return static_cast<int>(left);
    }
};

}

namespace SqrtTask
{

TEST(SqrtTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.mySqrt(4));
    ASSERT_EQ(2, solution.mySqrt(8));
}

}
