#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minFlips(int a, int b, int c) const
    {
        int flipCount = 0;
        for (int bit = 0; bit < 32; ++bit)
        {
            const int mask = 1 << bit;
            const int aValue = a & mask;
            const int bValue = b & mask;
            const int cValue = c & mask;
            if ((aValue | bValue) == cValue)
                continue;
            if (cValue == 0)
                flipCount += ((aValue > 0 ? 1 : 0) + (bValue > 0 ? 1 : 0));
            else
                ++flipCount;
        }
        return flipCount;
    }
};

}

namespace MinFlipsMakeAOrBEqualCTask
{

TEST(MinFlipsMakeAOrBEqualCTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minFlips(2, 6, 5));
    ASSERT_EQ(1, solution.minFlips(4, 2, 7));
    ASSERT_EQ(0, solution.minFlips(1, 2, 3));
}

}