#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minBitFlips(int start, int goal) const
    {
        size_t flipCount = 0;
        for (int value = start ^ goal; value != 0; value >>= 1)
        {
            if ((value & 1) == 1)
                ++flipCount;
        }
        return static_cast<int>(flipCount);
    }
};

}

namespace MinBitFlipsToConvertNumberTask
{

TEST(MinBitFlipsToConvertNumberTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minBitFlips(10, 7));
    ASSERT_EQ(3, solution.minBitFlips(3, 4));
}

}