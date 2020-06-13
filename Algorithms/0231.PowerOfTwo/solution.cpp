#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isPowerOfTwo(int n) const
    {
        for (int pow = 0, value = 1; pow <= 30; ++pow, value <<= 1)
        {
            if (n == value)
                return true;
            if (n < value)
                return false;
        }
        return false;
    }
};

}

namespace PowerOfTwoTask
{

TEST(PowerOfTwoTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isPowerOfTwo(1));
    ASSERT_EQ(true, solution.isPowerOfTwo(16));
    ASSERT_EQ(false, solution.isPowerOfTwo(218));
}

}