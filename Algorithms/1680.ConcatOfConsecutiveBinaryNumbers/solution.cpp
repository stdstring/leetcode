#include <cstdint>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int concatenatedBinary(int n) const
    {
        constexpr uint64_t modValue = 1000000007;
        uint64_t result = 0;
        int border = 2;
        int shift = 1;
        for (int current = 1; current <= n; ++current)
        {
            if (border == current)
            {
                ++shift;
                border <<= 1;
            }
            result <<= shift;
            result |= current;
            result %= modValue;
        }
        return static_cast<int>(result);
    }
};

}

namespace ConcatOfConsecutiveBinaryNumbersTask
{

TEST(ConcatOfConsecutiveBinaryNumbersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.concatenatedBinary(1));
    ASSERT_EQ(27, solution.concatenatedBinary(3));
    ASSERT_EQ(505379714, solution.concatenatedBinary(12));
}

}