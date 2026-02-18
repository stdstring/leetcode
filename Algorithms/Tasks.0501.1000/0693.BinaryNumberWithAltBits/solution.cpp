#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool hasAlternatingBits(int n) const
    {
        int prevBit = n & 1;
        n >>= 1;
        for (; n > 0; n >>= 1)
        {
            const int currentBit = n & 1;
            if (currentBit == prevBit)
                return false;
            prevBit = currentBit;
        }
        return true;
    }
};

}

namespace BinaryNumberWithAltBitsTask
{

TEST(BinaryNumberWithAltBitsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.hasAlternatingBits(5));
    ASSERT_EQ(false, solution.hasAlternatingBits(7));
    ASSERT_EQ(false, solution.hasAlternatingBits(11));
}

TEST(BinaryNumberWithAltBitsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.hasAlternatingBits(1));
}

}