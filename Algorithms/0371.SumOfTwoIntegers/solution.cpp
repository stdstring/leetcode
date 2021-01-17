#include <cstdint>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int getSum(int a, int b) const
    {
        int result = 0;
        const int bitsCount = 8 * sizeof(int);
        int carry = 0;
        for (int shift = 0; shift < bitsCount; ++shift)
        {
            const int bit = 1 << shift;
            const int aBit = a & bit;
            const int bBit = b & bit;
            result |= aBit ^ bBit ^ carry;
            carry = static_cast<uint32_t>((aBit & bBit) | (aBit & carry) | (bBit & carry)) << 1;
        }
        return result;
    }
};

}

namespace SumOfTwoIntegersTask
{

TEST(SumOfTwoIntegersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.getSum(1, 2));
    ASSERT_EQ(1, solution.getSum(-2, 3));
}

}