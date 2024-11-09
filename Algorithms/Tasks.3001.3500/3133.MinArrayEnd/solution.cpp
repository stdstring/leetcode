#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minEnd(int n, int x) const
    {
        if (n == 1)
            return x;
        --n;
        long long result = 0;
        long long currentBit = 1;
        for (int nMask = 1, xMask = 1; (nMask <= n) || (xMask <= x); currentBit <<= 1)
        {
            if ((xMask & x) == 0)
            {
                result |= ((n & nMask) == 0 ? 0 : currentBit);
                if (nMask <= n)
                    nMask <<= 1;
            }
            else
                result |= currentBit;
            if (xMask <= x)
                xMask <<= 1;
        }
        return result;
    }
};

}

namespace MinArrayEndTask
{

TEST(MinArrayEndTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.minEnd(3, 4));
    ASSERT_EQ(15, solution.minEnd(2, 7));
}

}