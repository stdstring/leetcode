#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isPowerOfFour(int num) const
    {
        return (num > 0) && ((num & (num - 1)) == 0) && ((num & 0b01010101010101010101010101010101) > 0);
    }
};

}

namespace PowerOfFourTask
{

TEST(PowerOfFourTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isPowerOfFour(16));
    ASSERT_EQ(false, solution.isPowerOfFour(5));
}

TEST(PowerOfFourTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isPowerOfFour(1));
    ASSERT_EQ(false, solution.isPowerOfFour(2));
    ASSERT_EQ(false, solution.isPowerOfFour(8));
}

}