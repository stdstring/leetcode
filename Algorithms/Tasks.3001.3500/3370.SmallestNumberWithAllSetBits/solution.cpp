#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int smallestNumber(int n) const
    {
        int result = 0;
        for (int bit = 1; bit <= n; bit <<= 1)
            result |= bit;
        return result;
    }
};

}

namespace SmallestNumberWithAllSetBitsTask
{

TEST(SmallestNumberWithAllSetBitsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.smallestNumber(5));
    ASSERT_EQ(15, solution.smallestNumber(10));
    ASSERT_EQ(3, solution.smallestNumber(3));
}

}