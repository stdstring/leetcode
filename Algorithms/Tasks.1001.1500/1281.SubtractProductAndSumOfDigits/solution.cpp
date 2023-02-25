#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int subtractProductAndSum(int n) const
    {
        int sum = 0;
        int product = 1;
        while (n > 0)
        {
            const int digit = n % 10;
            n /= 10;
            sum += digit;
            product *= digit;
        }
        return product - sum;
    }
};

}

namespace SubtractProductAndSumOfDigitsTask
{

TEST(SubtractProductAndSumOfDigitsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.subtractProductAndSum(234));
    ASSERT_EQ(21, solution.subtractProductAndSum(4421));
}

}