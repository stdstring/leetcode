#include <cstdint>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    uint32_t reverseBits(uint32_t n) const
    {
        const size_t size = 32;
        uint32_t result = 0;
        for (size_t shift = 0; shift < size; ++shift)
        {
            if (((1u << shift) & n) > 0)
                result |= (1u << (size - shift - 1));
        }
        return result;
    }
};

}

namespace ReverseBitsTask
{

TEST(ReverseBitsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(0b00111001011110000010100101000000u, solution.reverseBits(0b00000010100101000001111010011100u));
    ASSERT_EQ(0b10111111111111111111111111111111u, solution.reverseBits(0b11111111111111111111111111111101u));
}

}