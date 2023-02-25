#include <cstdint>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int hammingWeight(uint32_t n) const
    {
        const size_t size = 32;
        int count = 0;
        for (size_t shift = 0; shift < size; ++shift)
        {
            if ((n & (1u << shift)) > 0)
                ++count;
        }
        return count;
    }
};

}

namespace NumberOf1BitsTask
{

TEST(NumberOf1BitsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.hammingWeight(0b00000000000000000000000000001011u));
    ASSERT_EQ(1, solution.hammingWeight(0b00000000000000000000000010000000u));
    ASSERT_EQ(31, solution.hammingWeight(0b11111111111111111111111111111101u));
}

}