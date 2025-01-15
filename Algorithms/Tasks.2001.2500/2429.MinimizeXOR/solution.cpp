#include <bitset>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimizeXor(int num1, int num2) const
    {
        constexpr size_t bitCount = 32;
        std::bitset<bitCount> num1Bitset(num1);
        std::bitset<bitCount> num2Bitset(num2);
        std::bitset<bitCount> resultBitset(num1);
        size_t onesCount = num2Bitset.count();
        for (size_t rIndex = 0; (rIndex < bitCount) && (onesCount > 0); ++rIndex)
        {
            size_t index = bitCount - 1 - rIndex;
            if (resultBitset[index])
            {
                resultBitset[index] = false;
                --onesCount;
            }
        }
        for (size_t index = 0; (index < bitCount) && (onesCount > 0); ++index)
        {
            if (!num1Bitset[index])
            {
                resultBitset[index] = true;
                --onesCount;
            }
        }
        return static_cast<int>(resultBitset.to_ulong()) ^ num1;
    }
};

}

namespace MinimizeXORTask
{

TEST(MinimizeXORTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimizeXor(3, 5));
    ASSERT_EQ(3, solution.minimizeXor(1, 12));
}

}