#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int smallestNumber(int n, int t) const
    {
        for (int number = n; ; ++number)
        {
            if ((getDigitProduct(number) % t) == 0)
                return number;
        }
    }

private:
    [[nodiscard]] int getDigitProduct(int n) const
    {
        int result = 1;
        for (; n > 0; n /= 10)
            result *= (n % 10);
        return result;
    }
};

}

namespace TwoSumTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(10, solution.smallestNumber(10, 2));
    ASSERT_EQ(16, solution.smallestNumber(15, 3));
}

}