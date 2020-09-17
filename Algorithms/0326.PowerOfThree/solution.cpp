#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isPowerOfThree(int n) const
    {
        // std::numeric_limits<int>::max = 2147483647
        // 3^19 < std::numeric_limits<int>::max < 3^20
        // 3^19 = 1162261467
        return (n > 0) && (1162261467 % n == 0);
    }
};

}

namespace PowerOfThreeTask
{

TEST(PowerOfThreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isPowerOfThree(27));
    ASSERT_EQ(false, solution.isPowerOfThree(0));
    ASSERT_EQ(true, solution.isPowerOfThree(9));
    ASSERT_EQ(false, solution.isPowerOfThree(45));
}

}