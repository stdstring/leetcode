#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int bitwiseComplement(int n) const
    {
        if (n == 0)
            return 1;
        int result = 0;
        int factor = 1;
        while (n > 0)
        {
            if ((n & 1) == 0)
                result += factor;
            factor *= 2;
            n >>= 1;
        }
        return result;
    }
};

}

namespace ComplementOfBase10IntegerTask
{

TEST(ComplementOfBase10IntegerTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.bitwiseComplement(5));
    ASSERT_EQ(0, solution.bitwiseComplement(7));
    ASSERT_EQ(5, solution.bitwiseComplement(10));
}

}