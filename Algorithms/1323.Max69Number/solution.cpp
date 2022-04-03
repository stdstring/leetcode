#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximum69Number (int num) const
    {
        int factor = 1;
        while (factor <= num)
            factor *= 10;
        factor /= 10;
        int result = 0;
        while (num > 0)
        {
            const int digit = num / factor;
            num %= factor;
            if (digit == 6)
                return result + 9 * factor + num;
            result += digit * factor;
            factor /= 10;
        }
        return result;
    }
};

}

namespace Max69NumberTask
{

TEST(Max69NumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(9969, solution.maximum69Number(9669));
    ASSERT_EQ(9999, solution.maximum69Number(9996));
    ASSERT_EQ(9999, solution.maximum69Number(9999));
}

}